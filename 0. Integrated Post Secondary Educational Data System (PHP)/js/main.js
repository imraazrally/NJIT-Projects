function getListOfInstitutes(){
	$.ajax({
		url: 'ListOfInstitutes.php',
		success: function(success){
			$('#results').html(success);
		}
	});
}

function displayDetails(id){
	$.ajax({
		url:'Details.php',
		data:{'id':id},
		success: function(success){
			$('#detailedResults').html(success);
		}
	});
}


