jQuery(document).ready(function() {
  var sel_Mode;
  var sel_Prog;
	// set Mode
	jQuery('#setMode label').click(function() {
		sel_Mode = jQuery(this).children('input').val();
		if (sel_Mode==="MAN") {
			jQuery('#setProg').removeClass('hidden');
		} else {
			jQuery('#setProg').addClass('hidden');
		}
		jQuery('#Temp input[name=mode]').val(sel_Mode);
	})

	//set Program
	jQuery('#setProg label').click(function() {
		sel_Prog = jQuery(this).children('input').val();
		jQuery('#Temp input[name=mode]').val(sel_Mode+'/'+sel_Prog);
	})

})