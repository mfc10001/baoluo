<?php
/**
 * Created by PhpStorm.
 * User: ll
 * Date: 7/3/15
 * Time: 1:24 AM
 */
namespace token;



class TokenManager {
    private static $_instance;

    private   $config_player_exp=array();

    private function __construct(){
        echo 'This is a Constructed method;';
    }
    public function __clone(){
        trigger_error('Clone is not allow!',E_USER_ERROR);
    }
    public static function getInstance(){
        if(!(self::$_instance instanceof self)){
            self::$_instance = new self;
        }
        return self::$_instance;
    }

    //
    public $entry_manager=array();
    public $expire_time=3600;

    public  function  addToken($account,$token){
        if(!array_key_exists($account,$this->entry_manager)){
            $nowtime=time()+$this->expire_time;

            $this->entry_manager[$account]=array('token'=>$token,'account'=>$account,'valid_time'=>$nowtime);
        }
    }

    public function GetTokenInfo($account){
        if(array_key_exists($account,$this->entry_manager)){
            return  $this->entry_manager[$account];
        }
    }

    public function ToeknIsValid($account,$token){
        if(array_key_exists($account,$this->entry_manager)){
            $info=GetTokenInfo($account);
            if($info['valid_time']>=time()){
                if(strcmp($token,$info['token'])==0){
                    return true;
                }
            }

        }
        return false;
    }

    public function make_new_token(){
        $token='11111';
        return $token;
    }
};
?>