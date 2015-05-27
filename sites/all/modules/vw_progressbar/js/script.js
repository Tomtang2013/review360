jQuery(function () {

    var dropbox = jQuery('#dropbox'),
    message = jQuery('.message', dropbox);

    var maxfilesize = 1500000;
    dropbox.filedrop({
        // The name of the jQuery_FILES entry:
        paramname: 'pic',
        maxfiles: 1,
        maxfilesize: maxfilesize,
        isAuto:true,
//		url: './post_file.php',
        url: jQuery("#uploadFileTemp").val(),
//        drop:function(e){
//            
////            console.log(i);
////             console.log(file);
////            createImage(file,index );
//        },
        globalProgressUpdated: function(progress) {
         jQuery('#progress_num').html(progress);
        },
        uploadFinished: function (i, file, response) {
            if (response.error) {
                showMessage(response.status);
                jQuery(".preview").find("#item").text("");
            }
            jQuery.data(file).addClass('done');
            // response is the JSON object that post_file.php returns
        },
        error: function (err, file) {
            switch (err) {
                case 'BrowserNotSupported':
                    showMessage('Your browser does not support HTML5 file uploads!');
                    break;
                case 'TooManyFiles':
                    alert('Too many files! Please select 1 at most! (configurable)');
                    break;
                case 'FileTooLarge':
                    alert(file.name + ' is too large! Please upload files up to ' + maxfilesize + 'MB (configurable).');
                    break;
                default:
                    break;
            }
        },
        // Called before each upload is started
        beforeEach: function (file) {
            // checked in PHP side;

//			if(!file.type.match(/^image\//)
//                            && !file.type.match('image/png') ){
//				alert('Only images are allowed!');
//
//				// Returning false will cause the
//				// file to be rejected
//				return false;
//			}
        },
        uploadStarted: function (i, file, len) {
            createImage(file, i);
        },
        progressUpdated: function (i, file, progress) {
            jQuery.data(file).find('.progress').width(progress);
        }

    });

    var template = '<div class="preview">' +
            '<span class="imageHolder">' +
            '<img />' +
            '<span class="uploaded"></span>' +
            '</span>' +
            '<div class="progressHolder">' +
            '<div class="progress"></div>' +
            '</div>' +
            '</div>';
    function createImage(file) {

        var preview = jQuery(template),
        image = jQuery('img', preview);

        var reader = new FileReader();

        image.width = 100;
        image.height = 100;

        reader.onload = function (e) {
            // e.target.result holds the DataURL which
            // can be used as a source of the image:
            image.attr('src', e.target.result);
            image.css('width',100);
            jQuery('.drop-message').hide();
        };

        // Reading the file as a DataURL. When finished,
        // this will trigger the onload function above:
        reader.readAsDataURL(file);

        message.hide();
        preview.appendTo(dropbox);

        // Associating a preview container
        // with the file, using jQuery's jQuery.data():

        jQuery.data(file, preview);
    }

//    function createImage(file, index) {
//        var preview = jQuery(".preview");
//        var reader = new FileReader();
//
//        preview.find("#item").text(file.name);
//
//		reader.onload = function(e){
//			// e.target.result holds the DataURL which
//			// can be used as a source of the image:
//			image.attr('src',e.target.result);
//		};
//
//        // Reading the file as a DataURL. When finished,
//        // this will trigger the onload function above:
//        reader.readAsDataURL(file);
//
//        message.hide();
//
//        // replace the pre-uploaded file
//        dropbox.find(".preview").remove();
//
//        preview.appendTo(dropbox);
//
//        // Associating a preview container
//        // with the file, using jQuery's jQuery.data():
//
//        jQuery.data(file, preview);
//    }

    function showMessage(msg) {
        message.html(msg);
        message.show();
    }

});