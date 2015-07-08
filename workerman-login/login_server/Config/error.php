<?php
/**
 * Created by PhpStorm.
 * User: yubo.li
 * Date: 2015/7/8
 * Time: 11:28
 */

function compose_buffer($code,$type,$data=''){
    $buffer=array('code'=>$code,'type'=>$type,'data'=>$data);
    $buf= json_encode($buffer);
    return pack('v',strlen($buf)+2).$buf;
}

class ErrCode{
    const ERR_SUCCESS=0;
    const ERR_INNER=1;
    const ERR_PACK=2;
    const ERR_PWD=3;
    const ERR_PARAM=4;
}