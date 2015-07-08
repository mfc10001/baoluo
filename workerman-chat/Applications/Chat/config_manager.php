<?php
/**
 * Created by PhpStorm.
 * User: yubo.li
 * Date: 2015/6/30
 * Time: 11:14
 */
namespace config;


require_once __DIR__ . '/util/file.php';



class  ConfigManager{
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

    public function foo(&$v, $k, $kname) {

        $v = array_combine($kname, array_slice($v, 0));
    }

    public function Load_Exp_Config($file_path)
    {
        $cur=0;
        $name=array('id','grade','exp');
        if (file_exists($file_path)) {
            if ($fp = fopen($file_path, "r")) {
                while(!feof($fp)) {

                    $line = fgets($fp);
                    if ($cur < 3) {
                        $cur++;
                        continue;
                    }
                    $cur++;
                    $data = explode(',', $line);
                    $this->config_player_exp[$data[0]]=$data;

                }
                array_walk($this->config_player_exp, array($this,"foo"), $name);
            }else{
                echo "open Exp failded1\n";
            }
        }else{
            echo "open Exp failded2\n";
        }
    }


    public function Load_All_Config(){
        $path= __DIR__."/Config/res/";
        $this->Load_Exp_Config($path."role_exp.txt");
    }

    public function Get_Record_By_ID($type,$id){
        switch ($type)
        {
            case level:
                if(array_key_exists($id,$this->config_player_exp)){
                    return  $this->config_player_exp['id'];
                }
                break;
            default:
                return null;
        }
    }
}


?>