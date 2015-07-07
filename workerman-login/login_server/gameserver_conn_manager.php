<?php
/**
 * Created by PhpStorm.
 * User: ll
 * Date: 7/6/15
 * Time: 2:34 AM
 */

namespace conn;
class ConnManager
{
    private static $_instance;

    private $config_player_exp = array();

    private function __construct()
    {
        echo 'This is a Constructed method;';
    }

    public function __clone()
    {
        trigger_error('Clone is not allow!', E_USER_ERROR);
    }

    public static function getInstance()
    {
        if (!(self::$_instance instanceof self)) {
            self::$_instance = new self;
        }
        return self::$_instance;
    }

//
    private $ConnManager= array();

/*
    private $message_queue_key=null;
    private $message_queue=null;
    public function create_queue(){
       // $this->message_queue_key= ftok(/a/, 'a');;
        $this->message_queue = msg_get_queue($this->message_queue_key, 0666);
    }
    public function send_queue($data){
        msg_send($this->message_queue, 1, json_encode($data));
    }
*/
    public  function  init_conn($serverlist){
        foreach($serverlist as $key =>$value){
            init_gamesevrer($key,$value);
        }
/*
        $pid=pcntl_fork();
        if($pid==-1){ //进程创建失败
            die('fork child process failure!');
        }
        else if($pid){ //父进程处理逻辑
            pcntl_wait($status,WNOHANG);
        }
        else{ //子进程处理逻辑
            while(true){
                while(  $message_queue_status = msg_stat_queue($this->message_queue)){
                      if(  $message_queue_status['msg_qnum']>0){
                          msg_receive($this->message_queue, 0, $msgtype, 1024, $data);
                          $info= json_decode($data);
                          send_to_gameserver($info);
                      }
                }
                usleep( 1000 );
            }
        }
*/
    }

    function send_to_gameserver($data){
        socket_write($this->ConnManager[$data['sevrerid']],$data['userinfo']);
    }

    function init_gamesevrer($key,$addinfo){
        $socket = socket_create(AF_INET, SOCK_STREAM, SOL_TCP);
        $con=socket_connect($socket,'192.168.2.143',11109);
        if(!$con){socket_close($socket);exit;}
        $this->ConnManager[$key]=$con;

        /*
        $acpt=socket_accept($socket);
        echo "Acpt!\n";
        while ( $acpt ) {
            $words=fgets(STDIN);
            socket_write($acpt,$words);
            $hear=socket_read($acpt,1024);
            echo $hear;
            if("bye\r\n"==$hear){
                socket_shutdown($acpt);
                break;
            }
            usleep( 1000 );
        }
        */
    }
}


?>