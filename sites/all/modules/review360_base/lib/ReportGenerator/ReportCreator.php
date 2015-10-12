﻿<?php
//defined('DEFAULT_IMGPATH') or define('DEFAULT_IMGPATH', 'sites/default/files/generateFiles/Images/');
defined('DEFAULT_BGIMG') or define('DEFAULT_BGIMG', 'sites/default/files/generateFiles/Images/backgd.jpg');
defined('DEFAULT_IMGPATH') or define('DEFAULT_IMGPATH', 'sites/default/files/generateFiles/Images/');
//defined('DEFAULT_WORDPATH') or define('DEFAULT_WORDPATH', 'sites/default/files/generateFiles/');

class ReportCreator{
    private $_filePath;
    private $_outPutPath;
//    private $_data;
    public function __construct($filePath,$outPutPath) {
        $this->_filePath = $filePath;
        $this->_outPutPath = $outPutPath;

    }	
    public function generate_report($exam){

        require_once drupal_get_path('module', 'review360_base') . '/lib/PHPWord/PHPWord.php';
        require_once drupal_get_path('module', 'review360_base') . '/lib/ReportGenerator/ImageGenerator/ImageCreater.php';
        $PHPWord = new PHPWord();
        $document = $PHPWord->loadTemplate($this->_filePath);
        $document->setValue('company_name', iconv('utf-8', 'gbk', $exam->u_company_name));
        $document->setValue('user_name', iconv('utf-8', 'gbk', $exam->u_name));

        $document->setValue('position', iconv('utf-8', 'gbk', $exam->u_department));
        $document->setValue('date', iconv('utf-8', 'gbk', '2015年5月27日'));
        
        $document->setValue('work', iconv('utf-8', 'gbk', '动态 ==在工作情境中，你希望自己表现出的主要行为风格为D（支配型）。你希望自己可以表现出极高的成就感，好胜且有进取心，精力充沛，敢于挑战，果断自信，善于领导。'));
        $document->setValue('innate', iconv('utf-8', 'gbk', '动态 ==当你处于压力情境下时，你将会表现出自己最真实的动机与欲求，此时，你将会表现出的主要行为风格为D（支配型）、I（影响型）、S（稳健型）。此时，你目标明确，做事耐心坚定，精力充沛，善于交往。'));
        $document->setValue('outside', iconv('utf-8', 'gbk', '动态 ==你在平时工作中，最常表现出来的行为风格为D（支配型）。你有着极高的成就感，好胜且有进取心，精力充沛，敢于挑战，果断自信，善于领导。'));
        $document->setValue('suitable', iconv('utf-8', 'gbk', $exam->str->stress_desc->desc));
       
        $document->setValue('code', iconv('utf-8', 'gbk', $exam->str->rst_name));
        $document->setValue('classic', iconv('utf-8', 'gbk', $exam->str->rst_characteristic));
        $document->setValue('advantage', iconv('utf-8', 'gbk',$exam->str->rst_advantage));
        $document->setValue('deficiency', iconv('utf-8', 'gbk', $exam->str->rst_insufficient));
        $document->setValue('work_manifestation', iconv('utf-8', 'gbk', $exam->str->rst_work_performance));
       
        $img1 = new ImageCreater(DEFAULT_IMGPATH.'img1.png',DEFAULT_BGIMG,null);
        $img2 = new ImageCreater(DEFAULT_IMGPATH.'img2.png',DEFAULT_BGIMG,null);
        $img3 = new ImageCreater(DEFAULT_IMGPATH.'img3.png',DEFAULT_BGIMG,null);
        $img4 = new ImageCreater(DEFAULT_IMGPATH.'img4.png',DEFAULT_BGIMG,null);

        $img1->generate_image($exam->rst->in_working_me_value,true);
        $img2->generate_image($exam->rst->innate_value,true);
        $img3->generate_image($exam->rst->other_value,true);
        $img4->generate_image($exam->rst->stress_value,false);

        $document->save_image('image5.jpeg',DEFAULT_IMGPATH.'img1.png',$document);
        $document->save_image('image6.jpeg',DEFAULT_IMGPATH.'img2.png',$document);
        $document->save_image('image7.jpeg',DEFAULT_IMGPATH.'img3.png',$document);
        $document->save_image('image8.jpeg',DEFAULT_IMGPATH.'img4.png',$document);

        $doc = str_replace('w:val="A1A1A1"', 'w:val="ff6347"', $document->documentXML()); //C
        $doc = str_replace('w:val="A2A2A2"', 'w:val="ee82ee"', $doc);//I
        $doc = str_replace('w:val="A3A3A3"', 'w:val="98fb98"', $doc);//D
        $doc = str_replace('w:val="A4A4A4"', 'w:val="a0522d"', $doc);//S
        $doc = str_replace('w:themeColor="background2"', '', $doc);

        $document->set_documentXML($doc);
        $pix = $exam->nick_name."_".$exam->u_name;
        $file_name = $this->_outPutPath."/report_".$pix.".docx";
        $file_name = iconv('utf-8','gbk',$file_name); 
        $document->save($file_name);
        return $file_name;
    }
}
?>