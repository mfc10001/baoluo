<?php
/**
 * This file is part of workerman.
 *
 * Licensed under The MIT License
 * For full copyright and license information, please see the MIT-LICENSE.txt
 * Redistributions of files must retain the above copyright notice.
 *
 * @author walkor<walkor@workerman.net>
 * @copyright walkor<walkor@workerman.net>
 * @link http://www.workerman.net/
 * @license http://www.opensource.org/licenses/mit-license.php MIT License
 */
use Workerman\Worker;
use Workerman\Autoloader;
use conn\DbManager;
use conn\DB;
use conn\ConnManager;
use config\protocol;
use config\ErrCode;
use token\TokenManager;
// 自动加载类

require_once __DIR__ . '/../Workerman/Autoloader.php';

require_once __DIR__ . '/mysql_conn.php';
require_once __DIR__ . '/token_manager.php';
require_once __DIR__ . '/gameserver_conn_manager.php';
require_once __DIR__ . '/Config/protocol.php';
require_once __DIR__ . '/Config/error.php';

Autoloader::setRootPath(__DIR__);

// 开启的端口
$worker = new Worker('tcpscoket://0.0.0.0:22016');
// 启动多少服务进程
$worker->count = 1;
// worker名称，php start.php status 时展示使用
$worker->name = 'login';

DbManager::getInstance()->init_db_conn();

$db=DbManager::getInstance()->get_db_conn();
$server_data=array();
$sql="select * from serverinfo where GameID=1";
$result=$db->query($sql);
while($row=$db->fetch_assoc()){
    $server_data[$row['ID']]=$row;
}

$db->free();

function compose_buffer($code,$type,$data=''){
    $buffer=array('code'=>$code,'type'=>$type,'data'=>$data);
    $buf= json_encode($buffer);
    $len=strlen($buf)+2;
    return pack('v',$len).$buf;
}
ConnManager::getInstance()->init_conn($server_data);

$worker->onMessage = function($connection, $data)
{

    $message_data = json_decode($data, true);
    // 判断数据是否正确

    if(!$message_data)
    {
        return ;
    }
    if(empty($message_data['type']) )
    {
        // 发送数据给客户端，请求包错误
       return $connection->send(array('code'=>400,'type'=>'',  'data'=>null));
    }

    $db=DbManager::getInstance()->get_db_conn();
    global $server_data;
    $code=ErrCode::ERR_INNER;
    var_dump($message_data);
    switch(intval($message_data['type'])){
        case protocol::REGISETER_CS:
            if(empty($message_data['PassportID']) or empty($message_data['PassportPwd'] ))
            {
                return $connection->send(compose_buffer(ErrCode::ERR_PARAM,protocol::REGISETER_CS));
            }

            //$sql="call create_account('".$message_data['PassportID']."','".$message_data['PassportPwd']."')";
            $sql="INSERT into snsuserinfo (PassportID,PassportPwd)  values ('".$message_data['PassportID']."','".$message_data['PassportPwd']."')";
            echo $sql;
            $result=$db->query($sql);
            if ($row = $db->fetch_assoc())
            {
                if($row){
                    if(array_key_exists('code',$row)){
                        if($row['code']==0){
                            $code=ErrCode::ERR_SUCCESS;
                        }
                        else{
                            $code=ErrCode::ERR_PWD;
                        }
                    }
                }
            }
            else{
                $code=ErrCode::ERR_INNER;
                $data=mysql_error();
            }
            $db->free();

            return $connection->send(compose_buffer($code,protocol::REGISETER_CS,$data));
/*
            $sql="insert into snsuserinfo (PassportID,PassportPwd) VALUES ('".$message_data['PassportID']."','".$message_data['PassportPwd']."')";
            $result=$db->query($sql);
            if(!$result){
                $msg=$result.mysql_error();

                return $connection->send(compose_buffer(array('code'=>2, 'data'=>$msg)));
            }
            else{
                $msg['id']=$result.mysql_insert_id();
                return $connection->send(compose_buffer(array('code'=>0, 'data'=>$msg)));
            }
*/
        case protocol::LOGIN_CS:
            $account= $message_data['PassportID'];
            $pwd= $message_data['PassportPwd'];
            $sql="select PassportPwd,UserId from snsuserinfo where PassportID='".$account."'";

            $result=$db->query($sql);
            $row= $db->fetch_row($result);
            $token='';
            $userid='';
            if($row>0){
                if(strcmp($pwd,$row[0])==0){
                    $code=ErrCode::ERR_SUCCESS;
                    $token=TokenManager::getInstance()->make_new_token();
                    $userid=$row[1];
                    TokenManager::getInstance()->addToken($row[1],$token);
                }
                else{
                    $code=ErrCode::ERR_PWD;
                }
            }
            else {
                $code = ErrCode::ERR_INNER;
            }
            $db->free();
            return $connection->send(compose_buffer($code,protocol::LOGIN_CS,array('token'=>$token,'userid'=>$userid)));
        case protocol::SERVER_LIST_CS:
            $list=array();
            foreach($server_data as $key=>$value)
            {
                if(array_key_exists('ID',$value) && array_key_exists('ServerName',$value)){

                    $data=array('ID'=>$value['ID'],'ServerName'=>$value['ServerName']);
                    $k=$value['ID'];
                    var_dump($k);
                    $list[ $k]=$data;
                }
            }
            return $connection->send(compose_buffer(ErrCode::ERR_SUCCESS,protocol::SERVER_LIST_CS,$list));

        case protocol::CHOSE_SERVER_C:
            $serverid=$message_data['server'];
            if(count($server_data)>$serverid){
                $info = TokenManager::getInstance()->GetTokenInfo($message_data['id']);
                $info['type']='auth';
                ConnManager::getInstance()->send_to_gameserver($info);

                if(array_key_exists('Address',$server_data) or array_key_exists('Port',$server_data) ){
                    return $connection->send(compose_buffer(ErrCode::ERR_SUCCESS,protocol::SERVER_LIST_CS,$server_data[$serverid]));
                }
            }
            return true;
        case 8:
            return true;
        default:
            return false;

    }



    // 获得要调用的类、方法、及参数


    /*
    $class = $data['class'];
    $method = $data['method'];
    $param_array = $data['param_array'];
        
    StatisticClient::tick($class, $method);
    $success = false;
    // 判断类对应文件是否载入
    if(!class_exists($class))
    {
        $include_file = __DIR__ . "/Services/$class.php";
        if(is_file($include_file))
        {
            require_once $include_file;
        }
        if(!class_exists($class))
        {
            $code = 404;
            $msg = "class $class not found";
            StatisticClient::report($class, $method, $success, $code, $msg, $statistic_address);
            // 发送数据给客户端 类不存在
            return $connection->send(array('code'=>$code, 'msg'=>$msg, 'data'=>null));
        }
    }
     
    // 调用类的方法
    try 
    {
        $ret = call_user_func_array(array($class, $method), $param_array);
        StatisticClient::report($class, $method, 1, 0, '', $statistic_address);
        // 发送数据给客户端，调用成功，data下标对应的元素即为调用结果
        return $connection->send(array('code'=>0, 'msg'=>'ok', 'data'=>$ret));
    }
    // 有异常
    catch(Exception $e)
    {
        // 发送数据给客户端，发生异常，调用失败
        $code = $e->getCode() ? $e->getCode() : 500;
        StatisticClient::report($class, $method, $success, $code, $e, $statistic_address);
        return $connection->send(array('code'=>$code, 'msg'=>$e->getMessage(), 'data'=>$e));
    }
*/
};


// 如果不是在根目录启动，则运行runAll方法
if(!defined('GLOBAL_START'))
{
    Worker::runAll();
}
