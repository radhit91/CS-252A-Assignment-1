<form method="post" action="<?php echo $_SERVER['PHP_SELF'];?>">
	Forgot Password:<br>
	<table>
		<tr>
			<td>
				Username:
			</td>
			<td>
				<input type="text" name="username" value="">
			</td>
		</tr>
	</table>
	<br>
	
	
	<input type="submit">
</form>
<?php
if ($_SERVER["REQUEST_METHOD"] == "POST"){
	/*// Create connection
	echo "abcd";
	$conn = mysqli_connect("127.0.0.1","abhinav","@314_Pass");
	echo "xyzw";
	// Check connection
	/*if (!$conn) {
		die("Connection failed: " . $conn->connect_error);
	} 
	echo "Connected successfully";*/   
	$servername = "localhost";
	$username = "sec_user";
	$password = "eKcGZr59zAa2BEWU";

	// Create connection
	// 'About to Connect'."\n";
	$conn=mysqli_connect($servername,$username,$password,"secure_login");
	if (!$conn) {
    		error_log("Failed to connect to database!", 0);
	}
	//echo 'Connected'."\n";

	// Check connection
	if ($conn->connect_error) {
	    die("Connection failed: " . $conn->connect_error);
	}
	//echo 'Connected successfully'."<br>";
	$username=$_POST['username'];
	
	if($username!=NULL)
	{
		$sql="select * from members where username=".$username;
		$result = $conn->query($sql);
		if ($result->num_rows > 0) {
			// output data of each row
			while($row = $result->fetch_assoc()) {
			$question = $row['question'];
                        $answer = $row['answer'];
                        echo $question;
                        echo $answer;
                        echo "hello";
                        
			}
                        header("Location: /phpSecureLogin/password-1.php");
		}
                else
               {
                 echo "Entered Username is invalid";
               }
                
		
	}
	
	
}
?>
