<?php	
	
	class ImageCreater{
		
		private $_imageName;
		private $_background;
		private $_data;
		
		public function __construct($imageName,$background,$data) {
			$this->_imageName = $imageName;
			$this->_background = $background;
			$this->_data = $data;
		}			
		
		public function generate_image(){
//			$image = imagecreatefrompng($this->_background);
			$image = imagecreatefromjpeg($this->_background);
	
	//		$gray_color = imagecolorallocate($image, 162, 162, 162);               
	//		$red_color = imagecolorallocate($image, 255, 0, 0);  
	//		$yellow_color = imagecolorallocate($image, 0, 255, 0);
			$white_color = imagecolorallocate($image, 255, 255, 255);
			imagefilledellipse($image, 50, 50, 20, 20, $white_color);  
			imagefilledellipse($image, 120, 60, 20, 20, $white_color);  
			imagefilledellipse($image, 195, 100, 20, 20, $white_color);  
			imagefilledellipse($image, 265, 120, 20, 20, $white_color); 
			 
			imagesetthickness (  $image , 8 );
			imageline($image, 50, 50, 120, 60, $white_color);
			imageline($image, 120, 60, 195, 100, $white_color);
			imageline($image, 195, 100, 265, 120, $white_color);
			ob_clean();
			flush();
			
			Imagejpeg($image,$this->_imageName);
			ImageDestroy($image);
		}
		
	}

	
	
?>

