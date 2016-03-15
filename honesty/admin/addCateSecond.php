<?php
require_once '../include.php';
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<title>无标题文档</title>
</head>


<body>
<center>
<h3>添加二级分类</h3>
<form action="doAdminAction.php?act=addCateSecond" method="post">
<table width="70%" border="1" cellpadding="5" cellspacing="0" bgcolor="#cccccc">
<tr>
		<td align="right">一级分类名称</td>
		<td>
        

<select name="select">
<option value="0">请选择</option>
<?php
$relust = mysql_query("SELECT cName FROM honestycate where cpId=0");
while ($row = mysql_fetch_array($relust))
{
  echo "<option>".$row['cName']."</option>";
}
?>
</select>

        </td>
	</tr>
	<tr>
		<td align="right">二级分类名称</td>
		<td><input type="text" name="cName" placeholder="请输入分类名称"/></td>
	</tr>
	<tr>
		<td colspan="2"><input type="submit"  value="添加分类"/></td>
	</tr>

</table>
</form>
</center>
</body>
</html>