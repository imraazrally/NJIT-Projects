<?php
	class FilterHandler{
		private $dbConnection;
		private $instituteHandler;

		public function __construct($dbConnection,$instituteHandler){
			$this->dbConnection=$dbConnection;
			$this->instituteHandler=$instituteHandler;
		}

		/*
			@ParamType=stdObj [abbreviatedState, stateFullname];	
		*/

		public function getListOfStates(){
			/*
				This function returns a list of states the colleges belong to (abbreviated);
			*/

			$listOfStates=array();

			//Execute SQL
			$SQL="SELECT 
						DISTINCT (stabbr) AS abbreviatedState, 
						valuelabel AS stateFullName 

				  FROM base_table, frequencies WHERE codevalue=stabbr";
			
			$statement=$this->dbConnection->prepare($SQL);
			$statement->execute();

			//Fetch
			while($result=$statement->fetch(PDO::FETCH_OBJ)){
				array_push($listOfStates, $result);
			}

			//Returning an array that contains a list of abbreviated states
			return $listOfStates;
		}

		/*
			returnParam=stdObj[instnm,unitid]
			This function returns a list of unit id and names filtered by {state}{level}{medical}{hospital}
		*/
		

		public function getFilteredIdsAndNames($SQL,$name,$state,$level,$hospital,$medical){
			$listOfNamesAndIds=array();
			//Dynamically Building Query String Filtered
			
			$statement=$this->dbConnection->prepare($SQL);
			if(!empty($name))			$statement->bindParam(":name",$name);
			if(!empty($state)) 			$statement->bindParam(":state",$state);
			if(!empty($level))			$statement->bindParam(":level",$level);
			if(!empty($hospital))		$statement->bindParam(":hospital",$hospital);
			if(!empty($medical))		$statement->bindParam(":medical",$medical);
			$statement->execute();

			while($result=$statement->fetch(PDO::FETCH_OBJ)){
				array_push($listOfNamesAndIds,$result);
			}

			return $listOfNamesAndIds;

		}

	}

?>