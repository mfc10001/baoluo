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
use conn\ConnManager;
// 自动加载类

require_once __DIR__ . '/../Workerman/Autoloader.php';

require_once __DIR__ . '/mysql_conn.php';
require_once __DIR__ . '/token_manager.php';
require_once __DIR__ . '/gameserver_conn_manager.php';
Autoloader::setRootPath(__DIR__);


// 开启的端口
$worker = new Worker('tcpscoket://0.0.0.0:22016');
// 启动多少服务进程
$worker->count = 1;
// worker名称，php start.php status 时展示使用
$worker->name = 'login';


$db=DbManager::getInstance();
$db->init_db_conn();


$dbr=DbManager::getInstance()->get_db_conn();
$server_data=array();
$sql="select * from serverinfo";
$result=$dbr->query($sql);
while($row=$dbr->fetch_assoc()){
    $server_data[$row['id']]=$row;
}

function compose_buffer($buffer){
    $buf= json_encode($buffer);
    return strlen($buf).$buf;
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
       return $connection->send(array('code'=>400,  'data'=>null));
    }

    $db=DbManager::getInstance()->get_db_conn();
    global $server_data;

    var_dump($message_data);
    switch($message_data['type']){
        case 'register':

            if(empty($message_data['PassportID']) or $message_data['PassportPwd'] )
            {
                return $connection->send(compose_buffer(array('code'=>3, 'data'=>'')));
            }
           // $sql="select count(*) from snsuserinfo where PassportID='".$message_data['PassportID']."";
            $sql="call create_account('".$message_data['PassportID']."','".$message_data['PassportPwd']."')";
            $result=$db->query($sql);
            $row= $db->fetch_row($result);
            if($row>0){
                return $connection->send(compose_buffer(array('code'=>$row[0], 'data'=>'')));
            }
            return $connection->send(compose_buffer(array('code'=>2, 'data'=>'')));
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

        case 'login':
            $return = array('code'=>0,  'data'=>'');
            $account= $message_data['PassportID'];
            $pwd= $message_data['PassportPwd'];
            $sql="select PassportPwd,id from snsuserinfo where PassportID=".$account;
            $result=$db->query($sql);
            $row= $db->fetch_row($result);
            if($row>0){
                if(strcmp($pwd,$row[0])==0){
                    $return['code']=0;
                    TokenManager::getInstance()->addToken($row[1],TokenManager::getInstance()->make_new_token());
                }
                else{
                    $return['code']=1;
                }
            }
            else {
                $return['code'] = 2;
            }
            return $connection->send(json_encode($return));
        case 'server_list':
            return $connection->send(json_encode(array('code'=>0,  'data'=>$server_data)));

        case 'chose_server':
            $serverid=$message_data['server'];
            if(count($server_data)>$serverid){
              //  send_to_gamesevrer($server_data[$serverid]);

                $info = TokenManager::getInstance()->GetTokenInfo($message_data['id']);
                $info['type']='auth';
                ConnManager::getInstance()->send_to_gameserver($info);
            }
            return true;
        case 'inner_server':
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
