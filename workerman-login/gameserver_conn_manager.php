<?php
/**
 * Created by PhpStorm.
 * User: ll
 * Date: 7/6/15
 * Time: 2:34 AM
 */


class ConnManager
{
    private static $_instance;

    private $config_player_exp = array();

    private function __construct()
    {
        echo 'This is a Constructed method;';
        $message_queue_key = ftok(__FILE__, 'a');
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
    public  $message_queue_key=null;



    public function create_queue(){

        $message_queue = msg_get_queue($message_queue_key, 0666);

        $message_queue_status = msg_stat_queue($message_queue);
        print_r($message_queue_status);

//向消息队列中写
        msg_send($message_queue, 1, "Hello,World!");

        $message_queue_status = msg_stat_queue($message_queue);
        print_r($message_queue_status);

//从消息队列中读
        msg_receive($message_queue, 0, $message_type, 1024, $message, true, MSG_IPC_NOWAIT);
        print_r($message."\r\n");

    }

    public  function  init_conn($serverlist){
        foreach($serverlist as $key =>$value){
            init_gamesevrer($key,$value);
        }

        $pid=pcntl_fork();
        if($pid==-1){ //进程创建失败
            die('fork child process failure!');
        }
        else if($pid){ //父进程处理逻辑
            pcntl_wait($status,WNOHANG);
        }
        else{ //子进程处理逻辑
            while(true){
                while($this->msg_stat_queue.){

                }
                foreach($this->ConnManager as $key =>$value){

                }
            }

        }
    }




    function init_gamesevrer($key,$addinfo){
        $socket = socket_create(AF_INET, SOCK_STREAM, SOL_TCP);
        $con=socket_connect($socket,'192.168.2.143',11109);
        if(!$con){socket_close($socket);exit;}
        $this->ConnManager[$key]=$con;


        while($con){
            $hear=socket_read($socket,1024);
            echo $hear;
            $words=fgets(STDIN);
            socket_write($socket,$words);
            if($words=="bye\r\n"){break;}
        }
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