<?php
/**
 * Created by PhpStorm.
 * User: yubo.li
 * Date: 2015/7/7
 * Time: 14:55
 */
namespace Workerman\Protocols;

use Workerman\Connection\ConnectionInterface;

class tcpscoket implements \Workerman\Protocols\ProtocolInterface
{
    const MIN_HEAD_LEN = 6;



    public static function input($buffer, ConnectionInterface $connection)
    {
        // 数据长度
        $recv_len = strlen($buffer);
       // echo '$recv_len==='.$recv_len.'\n';
        // 长度不够
        if($recv_len < self::MIN_HEAD_LEN)
        {
            return 0;
        }

        $a=$buffer[0].$buffer[1];
        $data_len=ord($a) & 127;

       // echo '$data_len==='.$data_len.'\n';
        return $data_len;
    }

    public static function encode($buffer, ConnectionInterface $connection)
    {
        return $buffer;
    }
    public static function decode($buffer, ConnectionInterface $connection)
    {
        $a=$buffer[0].$buffer[1];
        $data_len=ord($a) & 127;
        $newbuffer= substr($buffer, 2, $data_len-2);
        return $newbuffer;
        /*
        $len = $masks = $data = $decoded = null;
        $len = ord($buffer[1]) & 127;
        if ($len === 126) {
            $masks = substr($buffer, 4, 4);
            $data = substr($buffer, 8);
        } else if ($len === 127) {
            $masks = substr($buffer, 10, 4);
            $data = substr($buffer, 14);
        } else {
            $masks = substr($buffer, 2, 4);
            $data = substr($buffer, 6);
        }

        for ($index = 0; $index < strlen($data); $index++) {
            $decoded .= $data[$index] ^ $masks[$index % 4];
        }
        $connection->websocketDataBuffer .= $decoded;
*/

    }
}

?>