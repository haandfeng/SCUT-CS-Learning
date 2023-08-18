package com.test.dao;

import com.test.pojo.User;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.List;



public class UserDao extends BaseDAO{

	public List<User> selectAll() {
		String sqlString="select * from t_user";
		return super.selectAll(sqlString, new Object[] {});
	}
	
	public User selectUserByName(String name) {
		String sqlString="select * from t_user where username =?";
		return super.select(sqlString, new Object[] {name});
	}


	public int updatePwd(String name,String pwd) {
		String sql="update  t_user set password = ? where username=?";

		return super.update(sql, new Object[] {pwd,name});
	}

	@Override
	public User rowMapper(ResultSet rs) {
		// TODO Auto-generated method stub
		User user=new User();
		try {
			user.setName(rs.getString("username"));
			user.setPassword(rs.getString("password"));
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
 		return user;
	}

}
