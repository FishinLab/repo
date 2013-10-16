<?
function match_email($email) 
{
    $email = $_POPST["input_str"];

    $pattern = "/^\w+([-+.]\w+)*@\w+([-.]\w+)*\.\w+([-.]\w+)*$/";
    $result_match = preg_match($pattern, $email);
    return $result_match;
}
$email_for_match = $_POST["input_str"];
match_email($email_for_match);
?>
