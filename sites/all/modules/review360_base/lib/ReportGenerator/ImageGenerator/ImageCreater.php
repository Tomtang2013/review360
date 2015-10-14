<?php

class ImageCreater {

    private $r = 15;
    private $line_width = 5;
    private $bar_width = 15;
    private $d_x_offset = 50;
    private $i_x_offset = 120;
    private $s_x_offset = 195;
    private $c_x_offset = 265;
    private $top_100_y_offset = 5;
    private $bottom_0_y_offset = 350;
//    private $middle_50_bottom_y_offset = 180;
    
    
    private $bar_d_x_offset = 80;
    private $bar_i_x_offset = 145;
    private $bar_s_x_offset = 210;
    private $bar_c_x_offset = 275;
    private $middle_50_y_offset = 133;
    private $bar_top_100_y_offset = 13;
    private $bar_bottom_0_y_offset = 252;
    private $_imageName;
    private $_background;
    private $_data;

    public function __construct($imageName, $background, $data) {
        $this->_imageName = $imageName;
        $this->_background = $background;
        $this->_data = $data;
    }

    private function calculate_value($value) {
        $rate = ($this->bottom_0_y_offset - $this->top_100_y_offset) / 100;
        return floor((100 - $value) * $rate);
    }
    
    private function calculate_bar_value($value) {
        $rate = ($this->bar_bottom_0_y_offset - $this->bar_top_100_y_offset) / 200;
        return $this->middle_50_y_offset -  floor(($value) * $rate);
    }

    public function generate_image($values, $is_line) {
        if ($is_line) {
            $this->render_image_line($values);
        } else {
            $this->render_image_bar($values);
        }
    }

    private function render_image_bar($values) {
        $image = imagecreatefromjpeg($this->_background);
        $d = $this->calculate_bar_value($values->d_value);
        $i = $this->calculate_bar_value($values->i_value);
        $s = $this->calculate_bar_value($values->s_value);
        $c = $this->calculate_bar_value($values->c_value);
        
        $white_color = imagecolorallocate($image, 0, 0, 0);
//        imagefilledrectangle($image, $this->bar_d_x_offset - $this->bar_width, $this->bar_top_100_y_offset, $this->bar_d_x_offset + $this->bar_width, $this->bar_bottom_0_y_offset, $white_color);
        imagefilledrectangle($image, $this->bar_d_x_offset - $this->bar_width, $this->middle_50_y_offset, $this->bar_d_x_offset + $this->bar_width, $d, $white_color);
        imagefilledrectangle($image, $this->bar_i_x_offset - $this->bar_width, $this->middle_50_y_offset, $this->bar_i_x_offset + $this->bar_width, $i, $white_color);
        imagefilledrectangle($image, $this->bar_s_x_offset - $this->bar_width, $this->middle_50_y_offset, $this->bar_s_x_offset + $this->bar_width, $s, $white_color);
        imagefilledrectangle($image, $this->bar_c_x_offset - $this->bar_width, $this->middle_50_y_offset, $this->bar_c_x_offset + $this->bar_width, $c, $white_color);

        ob_clean();
        flush();

        Imagejpeg($image, $this->_imageName);
        ImageDestroy($image);
    }

    private function render_image_line($values) {
//        $image = imagecreatefrompng($this->_background);
        $image = imagecreatefromjpeg($this->_background);

        $d = $this->calculate_value($values->d_value);
        $i = $this->calculate_value($values->i_value);
        $s = $this->calculate_value($values->s_value);
        $c = $this->calculate_value($values->c_value);

        $white_color = imagecolorallocate($image, 255, 255, 255);
        imagefilledellipse($image, $this->d_x_offset, $d, $this->r, $this->r, $white_color);
        imagefilledellipse($image, $this->i_x_offset, $i, $this->r, $this->r, $white_color);
        imagefilledellipse($image, $this->s_x_offset, $s, $this->r, $this->r, $white_color);
        imagefilledellipse($image, $this->c_x_offset, $c, $this->r, $this->r, $white_color);

        imagesetthickness($image, $this->line_width);
        imageline($image, $this->d_x_offset, $d, $this->i_x_offset, $i, $white_color);
        imageline($image, $this->i_x_offset, $i, $this->s_x_offset, $s, $white_color);
        imageline($image, $this->s_x_offset, $s, $this->c_x_offset, $c, $white_color);
        ob_clean();
        flush();

        Imagejpeg($image, $this->_imageName);
        ImageDestroy($image);
    }

}
?>

