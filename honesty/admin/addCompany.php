<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>Insert title here</title>
</head>
<body>
<h3>添加公司</h3>
<form action="doAdminAction.php?act=addCompany" method="post" enctype="multipart/form-data">
<table width="70%" border="1" cellpadding="5" cellspacing="0" bgcolor="#cccccc">
	<tr>
		<td align="right">公司名</td>
		<td><input type="text" name="companyname" placeholder="请输入要添加的公司名"/></td>
	</tr>
	<tr>
		<td align="right">密码</td>
		<td><input type="password" name="password" placeholder="请输入要添加的公司密码"/></td>
	</tr>
	<tr>
		<td align="right">邮箱</td>
		<td><input type="emain" name="email" placeholder="请输入公司邮箱"/></td>
	</tr>
	<tr>
		<td align="right">联系电话</td>
		<td><input type="text" name="telephone" placeholder="请输入公司联系电话"/></td>
	</tr>
	<tr>
		<td colspan="2"><input type="submit"  value="确认添加"/></td>
	</tr>

</table>
</form>
</body>
</html>