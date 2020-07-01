String TemplatePage = R"(
HTTP/1.1 200 OK 
Content-type:text/html 
Connection: close 

<!DOCTYPE html>
<html>
    <title>Garden Floodlights</title>
	<head>
		<meta name="viewport" charset="utf-8" content="width=device-width, initial-scale=1">
		<link rel="icon" href="data:,">
		<style>
			html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}
			.button { background-color: #195B6A; border: none; color: white; padding: 16px 40px; text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}
			.button2 {background-color: #77878A;}
			.pargraph{ color:green; font-size:40px;}
            .light{ color:green; font-size:20px;}
     .box{
    
      background:white;
      width:300px;
      border-radius:6px;
      margin: 0 auto 0 auto;
      padding:0px 0px 70px 0px;
      border: #2980b9 4px solid;}

  button {
     color: white;
     text-shadow: 1px 1px 2px black, 0 0 25px blue, 0 0 5px white;
    //box-shadow: 10px 10px 5px grey;
    border-radius: 55%;}
    
  .button:hover {background-color: #3e8e41}

    .button:active {
   background-color: #3e8e41;
   box-shadow: 10px 10px 5px grey;
   transform: translateY(4px);
    }

  h1{
    color: darkblue;
     text-shadow: 1px 1px 2px white, 0 0 25px blue, 0 0 5px white;
    }
            
		 </style>
	 </head>
<body>
<center>
    <div class="box">
		<h1>Floodlights Web Server</h1>
        <p class="pargraph">التحكم في إنارة الحديقة</p>
		    <p class="light"> Floodlight 1</p>
        <p><a href="/1/on"><button class="button">ON</button></a></p>
        <p class="light"> Floodlight 2</p>
        <p><a href="/2/on"><button class="button">ON</button></a></p>
        <p class="light"> Floodlight 3</p>
		    <p><a href="/0/on"><button class="button">ON</button></a></p>
		    <p class="light"> Click  Here! </p>
        <p><a href="/Festival"><button class="button">Festival</button></a></p>

</center>
</body></html>

)";
