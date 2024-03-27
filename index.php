<?php
    include('includes/bootstrap.inc.php');
?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
</head>
<body>
    <h3>Signup</h3>
    <form action="includes/formhandler.inc.php" method="post">
        <input type="text" name="username" placedholder="Username">
        <input type="password" name="password" placedholder="Password">
        <input type="text" name="email" placedholder="E-mail">
        <button>Signup</button>
    </form>
</body>
</html>