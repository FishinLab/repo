<?
session_start();

function image_redraw()
{
    header("content-type: image/PNG");
    srand((double)microtime()*1000000);
    $img = @imagecreate(62, 20);
    $black = imagecolorallocate($img, 0, 0, 0);
    $white = imagecolorallocate($img, 255, 255, 255);
    $gray = imagecolorallocate($img, 200, 200, 200);

    imagefill($img, 0, 0, $gray);
    $randval = rand() % 100000;
    $_SESSION["login_check_num"] = $randval;
    $_SESSION["extra"] = "extra";
    imagestring($img, 5, 10, 3, $randval, $black);

    for($i = 0; $i < 200; ++$i)
    {
        $randcolor = imagecolorallocate($img, rand(0, 255), rand(0, 255), rand(0, 255));
        imagesetpixel($img, rand() % 70, rand() % 30, $randcolor);
    }

    imagepng($img);
    imagedestroy($img);
}
image_redraw();
?>

