package com.test.utils;

import java.sql.*;

public class ConnDB {
	/**
	 * 连接数据库的操作，用户名，密码，使用jdbc连接
	 */
	public static String username = "root";
	public static String password = "0Woshizha";
	public static String url = "jdbc:mysql://127.0.0.1:3306/studentGrade?setUnicode=true&characterEncoding=utf8&useSSL=false&serverTimezone=UTC";

	static{
		try {
			Class.forName("com.mysql.cj.jdbc.Driver");
		} catch(ClassNotFoundException e){
			e.printStackTrace();
		}
	}

	public static Connection getConnection(){
		Connection conn = null;
		try{
			conn = DriverManager.getConnection(url,username,password);

		} catch (SQLException e){
			e.printStackTrace();
		}
		return conn;
	}
	// 关闭资源
	public  static void closeDB(ResultSet rs,Statement pst,Connection conn) {
		try {
			if(rs!=null) {
				rs.close();
			}
			if(pst!=null) {
				pst.close();
			}
			if(conn!=null) {
				conn.close();
			}
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	public static void main(String[] args) {
		System.out.println(ConnDB.getConnection());
	}
}
