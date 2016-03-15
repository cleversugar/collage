<?php
error_reporting(0);
$usercName="root";
$userpass="yy930209";
$dbhost="localhost";
$dbdatabase="honesty";
//生成一个连接
$db_connect=mysql_connect($dbhost,$usercName,$userpass) or die("Unable to connect to the MySQL!");
//选择一个需要操作的数据库
mysql_select_db($dbdatabase,$db_connect);
mysql_query("set names utf8");
//执行MySQL语句
$sqlwhere = "1=1";
if($_GET['cpId']!='' && $_GET['cpId']!='0'){
	$sqlwhere .= " and cpId='{$_GET['cpId']}'";
}
else{
	$sqlwhere .= " and cpId='0'";
	}
$result=mysql_query("SELECT id,cpId,cName FROM honestycate where {$sqlwhere}");
//提取数据
$date=array();
$i = 0;
while($row=mysql_fetch_array($result)){
	$date[$i]['id']=$row['id'];
	$date[$i]['cpId']=$row['cpId'];
	$date[$i]['cName']=$row['cName'];
	$i++;
}
$json = json_encode($date);
echo $json;
