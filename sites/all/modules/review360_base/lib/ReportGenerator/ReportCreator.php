<?php
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
        //$document = $PHPWord->loadTemplate('TemplateCopy.docx');
        $document = $PHPWord->loadTemplate($this->_filePath);
        $document->setValue('company_name', iconv('utf-8', 'gbk', '网易电子'));
        $document->setValue('user_name', iconv('utf-8', 'gbk', '王启发'));

        $document->setValue('position', iconv('utf-8', 'gbk', '高级警督'));
        $document->setValue('date', iconv('utf-8', 'gbk', '2015年5月27日'));
        $document->setValue('work', iconv('utf-8', 'gbk', '动态 ==在工作情境中，你希望自己表现出的主要行为风格为D（支配型）。你希望自己可以表现出极高的成就感，好胜且有进取心，精力充沛，敢于挑战，果断自信，善于领导。'));
        $document->setValue('innate', iconv('utf-8', 'gbk', '动态 ==当你处于压力情境下时，你将会表现出自己最真实的动机与欲求，此时，你将会表现出的主要行为风格为D（支配型）、I（影响型）、S（稳健型）。此时，你目标明确，做事耐心坚定，精力充沛，善于交往。'));

        $document->setValue('outside', iconv('utf-8', 'gbk', '动态 ==你在平时工作中，最常表现出来的行为风格为D（支配型）。你有着极高的成就感，好胜且有进取心，精力充沛，敢于挑战，果断自信，善于领导。'));
        $document->setValue('suitable', iconv('utf-8', 'gbk', '动态 ==“角色适应中的我”中需要关注中线上下超过+30%的部分，这反映了你适应的压力。如果D向上转换，可能面临结果与任务的压力；如果I向上转换，可能面临人际交往与开拓的压力；如果S向上转换，可能面临计划、执行与亲和的压力；如果C向上转换，可能面临工作规范、精确的压力。'));
        $document->setValue('classic', iconv('utf-8', 'gbk', '动态 ==你能量充沛，行为独特，非常追求新挑战与新机遇。有很强的自我力量。喜欢刺激，常常投入到不经深思的冒险中。为了达成目的，你会给人和环境提出要求，会勾画“蓝图”并充满激情地去推进实施。你最怕被受到控制与利用，在压力下可能会显得非常直率而缺乏沟通艺术。'));

        $document->setValue('advantage', iconv('utf-8', 'gbk', '动态 ==直接的，果断的；你具有强大的自我力量，通常是问题的解决者；你是冒险家，动力通常来自于你自身。'));
        $document->setValue('deficiency', iconv('utf-8', 'gbk', '动态 ==你有强烈的支配行为特征，有时候却可能显得过于武断权威；好争论，或过于盛气凌人；不喜欢常规，喜欢冒险却可能行动过急。'));
        $document->setValue('work_manifestation', iconv('utf-8', 'gbk', '动态 ==你具有领导与控制的才干，这些都是基于你直接的、高标准要求的天性。比较起需要紧密关系结合的工作情境来说，更适应于结构化的、正式的工作情境。你是非常具有竞争力与自信的人群，在信息缺乏的情势下，仍然能够迅速做出决策并实施计划。在他人看来极度困难的任务，对于你来说却可能“如鱼得水”。'));

        $img1 = new ImageCreater(DEFAULT_IMGPATH.'img1.png',DEFAULT_BGIMG,null);
        $img2 = new ImageCreater(DEFAULT_IMGPATH.'img2.png',DEFAULT_BGIMG,null);
        $img3 = new ImageCreater(DEFAULT_IMGPATH.'img3.png',DEFAULT_BGIMG,null);
        $img4 = new ImageCreater(DEFAULT_IMGPATH.'img4.png',DEFAULT_BGIMG,null);

        $img1->generate_image();
        $img3->generate_image();
        $img2->generate_image();
        $img4->generate_image();

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
        $pix = $exam->s_id."_".$exam->nick_name;
//        $pix = iconv('utf-8', 'gbk', $user->u_name) ;
        $document->save($this->_outPutPath."/report_".$pix.".docx");
    }
}
?>