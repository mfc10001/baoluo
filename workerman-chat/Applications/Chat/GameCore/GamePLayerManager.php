<?php
/**
 * Created by PhpStorm.
 * User: ll
 * Date: 7/5/15
 * Time: 6:48 PM
 */
    class GamePlayerManager {
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

    };
?>