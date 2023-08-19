package com.test.dao;




import com.test.pojo.Teacher;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;


public class TeacherDao extends BaseDAO{

	public List<Teacher> selectAll(){
		//return new ArrayList<Teacher>();
		String sql="select * from v_tea_course ";
		return super.selectAll(sql, new Object[] {});
	}

	public Teacher selectByTno(String cno){
		//return new ArrayList<Teacher>();
		String sql="select * from v_tea_course where tno=?";
		return super.select(sql, new Object[] {cno});
	}
	
//	添加记录
	public int insertTeacher(Teacher teacher) {
		String sql="insert into  teacher (tno,tname) VALUES (?,?)";
		return super.update(sql, new Object[] {
				teacher.getTno(),
				teacher.getTname(),
				
		});
	}

	public int update(Teacher teacher) {
		String sql = "update teacher set tname=?  where tno=?";
		return super.update(sql, new Object[]{

				teacher.getTname(),
				teacher.getTno(),
				
		});
	}

	public int updatePwd(String tno,String pwd) {
		String sql="update  teacher set password = ? where tno=?";

		return super.update(sql, new Object[] {pwd,tno});
	}

//	根据sno查找记录
	public List<Teacher> select(Teacher teacher) {
		StringBuilder builder = new  StringBuilder();
		String sql="select * from v_tea_course where  1=1";
		ArrayList<Object> list = new ArrayList<>();
		
		builder.append(sql);
		if (!teacher.getTno().equals("".trim())){
			builder.append(" and tno LIKE ?");
			list.add('%' +teacher.getTno()+  '%');
		}
		if (!teacher.getTname().equals("".trim())){
			builder.append(" and tname LIKE ?");
			list.add('%' +teacher.getTname()+  '%');
		}



		return super.selectAll(builder.toString(), list.toArray());
	}

	//	根据sno查找记录
	public String selectSql(Teacher teacher) {
		StringBuilder builder = new  StringBuilder();
		String sql="select * from v_tea_course where  1=1";

		builder.append(sql);
		if (!teacher.getTno().equals("".trim())){
			builder.append(" and tno LIKE '%" +teacher.getTno() + "%'");

		}
		if (!teacher.getTname().equals("".trim())){
			builder.append(" and tname LIKE '%" +teacher.getTname() + "%'");

		}

		return builder.toString();
	}

	
	//	根据sno修改数量
	public int del(String sno) {
		String sql="delete from teacher where tno=?";

		return super.update(sql, new Object[] {sno});
	}



	
	
	@Override
	public Teacher rowMapper(ResultSet rs) {
		// TODO Auto-generated method teacherb
		Teacher teacher=new Teacher();
		try {
			teacher.setTno(rs.getString("tno"));
			teacher.setTname(rs.getString("tname"));
			teacher.setCourses(rs.getString("courses"));
			teacher.setPassword(rs.getString("password"));

		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return teacher;
	}
	
}
