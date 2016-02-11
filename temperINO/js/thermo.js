jQuery(document).ready(function() {

	// set Mode
	jQuery('#setMode label').click(function() {
		var sel_Mode = jQuery(this).children('input').val();
		if (sel_Mode==="MAN") {
			jQuery('#setProg').removeClass('hidden');
		} else {
			jQuery('#setProg').addClass('hidden');
		}
		jQuery('#Temp input[name=mode]').val(sel_Mode);
	})

	//set Program
	jQuery('#setProg label').click(function() {
		var sel_Prog = jQuery(this).children('input').val();
		jQuery('#Temp input[name=program]').val(sel_Prog);
	})

})