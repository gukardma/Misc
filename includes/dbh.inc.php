<?php

   //***** DB Connection */
    //params necessary for connecting using PDO object
    $dsn = "mysql:host:=localhost;dbname=funtimes";
    $dbusername = "root";
    $dbpassword = "";


    try {
        $pdo = new PDO($dsn, $dbusername, $dbpassword); //connection to database
        $pdo->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION); //if we get an error, throw an exception
    } catch (PDOException $e) {
        echo "Connection failed: " . $e->getMessage(); //Get the exception, and return the error message in browser
    }