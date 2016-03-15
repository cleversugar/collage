<?php
require_once '../include.php';
checkLogined();
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<title>无标题文档</title>
<link type="text/css" rel="stylesheet" href="style/public.css">
<link type="text/css" rel="stylesheet" href="style/reset.css">
<link type="text/css" rel="stylesheet" href="style/main.css">
<link rel="stylesheet" type="text/css" href="style/adminStyle.css"/>

<script src="script/jquery.js" type="text/javascript"></script>

<script type="text/javascript">
$(function(){
		$('.menubar>a').click(function(){
			$(this).parent().find('ul').toggle('slow');
			//$(this).toggleClass('cur');
		});
	});
    	
</script>
</head>

<body>
<div class="headerBar">
	<div class="topBar">
		<div class="comWidth">
			<div class="leftArea">
      &nbsp;&nbsp;&nbsp;&nbsp; <a href="../index.php">诚聘网</a> &gt;&gt;<a href="admin_index.php">后台管理</a></div>
			<div class="rightArea">
				 亲爱的
				   <?php 
				if(isset($_SESSION['adminName'])){
					echo $_SESSION['adminName'];
				}elseif(isset($_COOKIE['adminName'])){
					echo $_COOKIE['adminName'];
				}
            ?>
				   ，欢迎来到<a href="admin_index.php">诚聘网</a>管理员界面！<a href="doAdminAction.php?act=logout" class="icon icon_e">[退出登录]</a>
			</div>
	      <iframe src="main.php"  frameborder="0" name="mainFrame" width="800" height="522"></iframe>
		</div>
	</div>
</div>
<div class="adminbar">
<ul>
<li> &nbsp;管理员</li>
<li>|</li>
<li></li>
</ul>
</div> 
<div class="main">

<div class="mainLeft">
          <ul class="list">
  <li class="menubar"> 
                  <a>管理管理员</a>
                  <ul> 
                    <li><a href="listAdmin.php" target="mainFrame">查看管理员</a></li> 
                    <li><a href="addAdmin.php" target="mainFrame">添加新管理员</a></li>
                    
                  </ul> 
                </li>
	</ul>
     <ul class="list">
<li class="menubar"> 
                  <a>管理职位分类</a>
                  <ul> 
                    <li><a>查看分类信息</a></li> 
                    <li>
                    <ul class="list">
                    <li class="menubar"> 
                      <a>添加分类</a>
                    <ul> 
                    <li ><a href="addCateFirst.php" target="mainFrame">&nbsp;&nbsp;添加一级分类</a></li>
                    <li><a href="addCateSecond.php" target="mainFrame">&nbsp;&nbsp;添加二级分类</a></li>
                    <li><a>&nbsp;&nbsp;添加三级分类</a></li>                    </ul>                    
                    </li>			
			</ul>
                    </li>
                    
                  </ul> 
                </li>			
			</ul>
            <ul class="list">
<li class="menubar"> 
                  <a>管理用户</a>
                  <ul> 
                    <li><a>查看用户信息</a></li> 
                    <li><a>添加新用户</a></li>
                    <li><a>修改用户信息</a></li>
                    <li><a>删除用户</a></li>
                  </ul> 
                </li>			
			</ul>
            <ul class="list">
<li class="menubar"> 
                  <a>管理公司</a>
                  <ul> 
                    <li><a>查看公司信息</a></li> 
                    <li><a>添加新公司</a></li>
                    <li><a>修改公司信息</a></li>
                    <li><a>删除公司</a></li>
                  </ul> 
                </li>			
			</ul>
     
</div>
    <div class="content clearfix">

<div class="mainRight">
               <!--<div class="title">后台管理</div>
      	 		 嵌套网页开始 --><!-- 嵌套网页结束 --> 
</div></div>
</div>
<div class="tail">
<ul>
<li>法律声明 | 关于我们 | 注册协议<li> 
<li>Copyright &copy;上海理工大学 唐颖 版权所有 翻版必究</li> 
<li>地址:上海理工大学 电话(Tel):12345678 EMAIL:admin@admin.com</li> 
</ul>
</div>
</body>
</html>