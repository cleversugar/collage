<?php
require_once '../include.php';
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<title>无标题文档</title>
<script src="script/jquery-1.11.0.min.js"></script>

</head>


<body>
<center>
<h3>添加三级分类</h3>
<form name="form1" action="doAdminAction.php?act=addCateThird" method="post">
  <table width="70%" border="1" cellpadding="5" cellspacing="0" bgcolor="#cccccc">
  <tr>
		<td align="right">一级分类名称</td>
		<td><select name="select1" id="select1" onChange="getClass(this.value)">
    <option value="0">请选择</option></select></td>
	</tr>
      <td align="right">二级分类名称</td>
		<td><select name="select2" id="select2">
    <option value="0">请选择</option>
  </select></td>
	</tr>
	<tr>
		<td align="right">三级分类名称</td>
		<td><input type="text" name="cName" placeholder="请输入分类名称"/></td>
	</tr>
	<tr>
		<td colspan="2"><input type="submit"  value="添加分类"/></td>
	</tr>

</table>
</form>
</center>
<script>
getClass();
function getClass(id){
	if(id==null){
		id=0;
	}
	$.ajax({
		type: "GET",
		url: "getSelect.php",
		global:"false",
		data:"cpId=" + id,
		dataType:"json",
		error:function(){
			alert('与服务器通讯出错！');
			return false;
		},
		success: function(msg){
			if(id==0){
				$('#select1').html('<option value="0">请选择</option>');
				$('#select2').html('<option value="0">请选择</option>');
				for(var i=0;i<msg.length;i++){
					$('#select1').append('<option value="'+msg[i].id+'">'+msg[i].cName+'</option>');
				}
			}else{
				$('#select2').html('<option value="0">请选择</option>');
				if(msg.length>0){
					for(var i=0;i<msg.length;i++){
						$('#select2').append('<option value="'+msg[i].id+'">'+msg[i].cName+'</option>');
					}
				}else{
					$('#select2').html('<option value="0">请选择</option>');
				}
			}
		},
		complete:function(){
		}
	});
}
</script>

</body>
</html>