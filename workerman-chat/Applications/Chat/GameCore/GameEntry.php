<?php
/**
 * Created by PhpStorm.
 * User: yubo.li
 * Date: 2015/6/30
 * Time: 10:52
 */
namespace GameCore;

class GameEntry{
    // private $base_attribute;
    protected $n_id =0;
    protected $n_name="";
    protected $n_quality=0;
    protected $n_profession=0;
    protected $n_skillId =0;
    protected $n_attackRange=0;
    protected $n_attactSpeed =0;
    protected $n_speed=0;
    protected $n_bcritDamage=0;
    protected $exp=0;
    protected $level=0;

    protected $base_attribute=array();
    protected $attribute_grew=array();
    public function init(){
        $this->id=1233333;
    }


    public function __construct() {
        // $base_attribute=new GameBaseDefine();
        $this->base_attribute['n_physicsAttack']=0;
        $this->base_attribute['n_magicAttack']=0;
        $this->base_attribute['n_barmor']=0;
        $this->base_attribute['n_bresistance']=0;
        $this->base_attribute['n_hp']=0;
        $this->base_attribute['n_hit']=0;
        $this->base_attribute['n_dodge']=0;
        $this->base_attribute['n_crit']=0;
        $this->base_attribute['n_opposeCrit']=0;


        $this->attribute_grew['n_physicsAttackz']=0;
        $this->attribute_grew['n_magicAttackz']=0;
        $this->attribute_grew['n_barmorz']=0;
        $this->attribute_grew['n_bresistancez']=0;
        $this->attribute_grew['n_hpz']=0;
        $this->attribute_grew['n_hitz']=0;
        $this->attribute_grew['n_dodgez']=0;
        $this->attribute_grew['n_critz']=0;
        $this->attribute_grew['n_opposeCritz']=0;


        $this->init();
    }


};

?>