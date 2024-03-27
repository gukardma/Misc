<?php
    include('includes/bootstrap.inc.php');
?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
    <link rel="stylesheet" href="css/styles.css">
</head>
<body>
    <div class="modal" id="login-modal">
        <h3>Signup</h3>
        <form action="includes/formhandler.inc.php" method="post">
            <input type="text" name="username" placeholder="Username">
            <input type="password" name="password" placeholder="Password">
            <input type="text" name="email" placeholder="E-mail">
            <button onclick=toggleLoginModal()>Signup</button>
        </form>
    </div>
    <div class="website" id="rest">
        <t>This is the rest of the website</t>
    </div>
</body>
</html>