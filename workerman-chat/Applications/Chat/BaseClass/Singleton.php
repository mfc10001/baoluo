<?php
namespace base;
/**
 * Created by PhpStorm.
 * User: yubo.li
 * Date: 2015/6/30
 * Time: 17:56
 */

class Singleton{
    private static $_instance;
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
}

?>