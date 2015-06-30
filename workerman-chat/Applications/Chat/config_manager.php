<?php
/**
 * Created by PhpStorm.
 * User: yubo.li
 * Date: 2015/6/30
 * Time: 11:14
 */
namespace config;

require_once __DIR__ . '/excel_reader2.php';


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

    public function Load_Exp_Excel($file){
        $data = new Spreadsheet_Excel_Reader($file);
        if($data==null || $data->colcount()!=3)
        {
            die();
        }
        for($i=0;$i<$data->rowcount();$i++){
            if($i<3){
                continue;
            }
            $exp=array(
                "id"   => '',
                "grade"   => '',
                "exp" => '',
             );
            $j=0;
            foreach($exp as $key=>$value){
                $exp[$key]=$data->val($i,$j);
                $j+=1;
            }
            $config_player_exp[$exp['id']]=$exp;
        }
        var_dump($this->config_player_exp);
    }

    public function Load_All_Config(){
        $path="./Config/res/";
        $this->Load_Exp_Excel($path."role_exp.xls");
    }

    public function Get_Record_By_ID($type,$id){
        switch ($type)
        {
            case 'exp':
                return  $this->config_player_exp['id'];

        }
    }
}


?>