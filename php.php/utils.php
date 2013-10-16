<?php

    session_start();

    function handle_sql_exceptions($sql_error_str)
    {
        if(empty($sql_error_str)) return;
        $err_sqls_path = "../sys_logs/error_sqls";
        error_log("$sql_error_str \n", 3, $err_sqls_path);
        header("LOCATION: http://fronts/error_page.html");
    }

    function write_back($o_mysqli )
    {
        global $_SESSION;

        if($o_mysqli->connect_errno) die("mysqli instance should be initialized\n");
        
        if(!$_SESSION["last_operation_id"])
        {
            try
            {
                $pro_id = $_SESSION["last_operation_id"];
                $wb_sql = "update time_out_infos set last_operation = now()
                    where related_problem_id = $pro_id;";
                $o_mysqli->query($wb_sql); 
            }catch(mysqli_sql_exception $ex)
            {
                die($ex->errorMessage());
            }
            $o_mysqli->close();
        }
        $_SESSION["last_operation_id"] = NULL;
        session_write_close();
        $kill_session();
    }

    function check_session($session_id)
    {
        if(session_id() == $session_id) return true;
        else
        {
            header();
            return false;
        }
        return false;
    }

    function kill_session($session_id)
    {
        #kill user session by hand     
    }

    function check_problem_timeout($p_obj, $o_mysqli)
    {
        #this task will be croned by root 
    }

#DEBUG:
    $_SESSION = array(
        "user_id" => "1"
        );

    function salt_n_md($passwd)
    {
#FIXME
#   do not use magic number here, but i do not know how to choose them
#   GIVE ME A SIGN!!!
        $salt_source = ""; 
#BUG: (by FisHinLab)
        #for($i = 0; $i < 8; ++$i) $salt_source .= rand(0, 9); 
        for($i = 1; $i < $passwd->length;) 
        {
            $salt_source .= $passwd[$i];
            $i += $i; 
        } 
        $salt = MD5($salt_source);
        return MD5($salt.$passwd);
    }

    function ajax_db_op($header_to, $table_name) 
    {
        try 
        {
            $o_mysqli = new mysqli($host_name, $db_user, $db_pwd, $db_name); 
            $get_table_len_sql = "select count(*) from $table_name;";
             
        }catch(Exception $ex)
        {
            $ex->errorMessage(); 
        }
    }

#ENCRYPT METHOD
    function encode($txt)
    {
        $txt = trim($txt);
        $my_array = array(
            "cpp","java","ruby","asp","php",
            "javascript","ajax","css","jquery","html"
            );
        $my_key = sha1($my_array[rand(0, 9)]);
        $str = 0;
        $tmp = "";
        for($i = 0; $i < strlen($txt); ++$i)
        {
            $str = $str == strlen($my_key) ? 0 : $str;
            $tmp .= $my_key[$str].($txt[$i] ^ $my_key[$str++]);
        }

        $key = "pixel";
        $key = sha1($key);
        $str_1 = 0;
        $tmp_1 = "";
        for($i = 0; $i < strlen($tmp); ++$i)
        {
            $str_1 = $str_1 == strlen($key) ? 0 : $str_1;
            $tmp_1 .= $tmp[$i] ^ $key[$str_1++];
        }
        return trim(chop(base64_encode($tmp_1)));
    }

#DECODE METHOD
    function decode($txt)
    {
        $txt = trim($txt);
        $txt = base64_decode($txt);
        $key = "pixel";
        $key = sha1($key);
        $str_1 = 0;
        $tmp_1 = "";
        for($i = 0; $i < strlen($txt); ++$i)
        {
            $str_1 = $str_1 == strlen($key) ? 0 : $str_1;
            $tmp_1 .= $txt[$i] ^ $key[$str_1++];
        }

        $tmp = "";
        for($i = 0; $i < strlen($tmp_1); ++$i)
        {
            $tmp_1_i = $tmp_1[$i];
            $tmp .= $tmp_1[++$i] ^ $tmp_1_i;
        }
        return trim(chop($tmp));
    }

?>
