<?php
/**
 * Created by PhpStorm.
 * User: yubo.li
 * Date: 2015/6/30
 * Time: 17:54
 */
use \base\Singleton;

class GamePlayerManager extends  Singleton{
    public $player_manager=null;

    public function add_player($player){
        $player_manager[$player->id]=$player;
    }
}