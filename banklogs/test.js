/**
 * Function : dump()
 * Arguments: The data - array,hash(associative array),object
 *    The level - OPTIONAL
 * Returns  : The textual representation of the array.
 * This function was inspired by the print_r function of PHP.
 * This will accept some data as the argument and return a
 * text that will be a more readable version of the
 * array/hash/object that is given.
 * Docs: http://www.openjs.com/scripts/others/dump_function_php_print_r.php
 */
function dump(arr,level) {
    var dumped_text = "";
    if(!level) level = 0;
    if(level == 2) return "";
    
    //The padding given at the beginning of the line.
    var level_padding = "";
    for(var j=0;j<level+1;j++) level_padding += "    ";
    
    if(typeof(arr) == 'object') { //Array/Hashes/Objects 
        for(var item in arr) {
            var value = arr[item];
            
            if(typeof(value) == 'object') { //If it is an array,
                dumped_text += level_padding + "'" + item + "' ...\n";
                dumped_text += dump(value,level+1);
            } else {
                dumped_text += level_padding + "'" + item + "' => \"" + value + "\"\n";
            }
        }
    } else { //Stings/Chars/Numbers etc.
        dumped_text = "===>"+arr+"<===("+typeof(arr)+")";
    }
    return dumped_text;
}

$('#taglist').live('listviewcreate', function() {
  var list = $(this),
    listview = list.data('listview');

  if(listview.options.filter == false)
  {
    return;
  }

  var form = $(this).parent().find('form');

  form.submit(function(){
    var newid = $(this).find('input').val();
    form.attr('action', 'add_tag.php?tag=' + newid);
    form.attr('method', 'POST');

    $.post(
      "add_tag.php", { tag: newid }, function(data) {
        alert("Result : " + data);
        window.location.reload(true);
      }
    );

    /*
    $.ajax({
      url: 'example.xml',
      dataType: 'xml',
      success: function(msg) {
        alert('done');
        window.location.reload(true);
      }
    });
    */

    /*
    $('<a href="#">Switch</a>')
      .text(newid)
      .buttonMarkup({
              'icon':'gear',
              'inline': true,
              'shadow': false,
              'theme': 'd'
      })
      .appendTo( $(this).parent() )
      .wrap('<div class="jqm-themeswitcher">')
      .click(function(){
        alert(dump($(this)));
        return false;
      });
    */
    return false;
  });
});

$('#tagselectlist').live('listviewcreate', function() {
  var list = $(this),
    listview = list.data('listview');

  list.find("a").click(function()
  {
    alert($(this).data("logid") + " " + $(this).data("tagid") + " " + $(this).data("tagged"));
    $.post(
      "settag.php", { logid: $(this).data("logid"), tagid: $(this).data("tagid"), tagged: $(this).data("tagged") }, function(data) {
        alert("Result : " + data);
        window.location.reload(true);
      }
    );
    return false;
  });
    /*
    $.ajax({
      url: 'example.xml',
      dataType: 'xml',
      success: function(msg) {
        alert('done');
        window.location.reload(true);
      }
    });
    */
});
