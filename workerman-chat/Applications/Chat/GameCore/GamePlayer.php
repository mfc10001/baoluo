<?php
namespace GameCore;
use \GameCore\GameEntry;
use \config\ConfigManager;
/**
 * Created by PhpStorm.
 * User: ll
 * Date: 6/28/15
 * Time: 7:11 PM
 */


    class GamePlayer extends  GameEntry{

        public  function  level_up(){
            $row= ConfigManager::getInstance()->Get_Record_By_ID(level,$this->level);
            if(!$row){return;}
            if($this->exp>=$row->data['next']){

                $this->exp=$this->exp-$row->data['next'];
                $this->level++;
            }
        }
        public function add_exp($num){
            $this->exp+=$num;
            call_user_func_array(array("GamePlayer","level_up"),array());
        }

    };
?>