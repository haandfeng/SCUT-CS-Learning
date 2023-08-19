package com.test.dao;




import com.test.pojo.Student;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;


public class StudentDao extends BaseDAO{

	public List<Student> selectAll(){
		//return new ArrayList<Student>();
		String sql="select * from student ";
		return super.selectAll(sql, new Object[] {});
	}

	public Student selectBySno(String sno){
		//return new ArrayList<Course>();
		String sql="select * from student where sno=?";
		return super.select(sql, new Object[] {sno});
	}

	
//	添加记录
	public int insertStudent(Student stu) {
		String sql="insert into  student (sno,sname,ssex,entrance_age,entrance_year,class) VALUES (?,?,?,?,?,?)";
		return super.update(sql, new Object[] {
				stu.getSno(),
				stu.getSname(),
				stu.getSsex(),
				stu.getEntranceAge(),
				stu.getEntranceYear(),
				stu.getClazz()
		});
	}

	public int update(Student stu) {
		String sql = "update student set sname=?,ssex=?,entrance_age=?,entrance_year=?,class=? where sno=?";
		return super.update(sql, new Object[]{

				stu.getSname(),
				stu.getSsex(),
				stu.getEntranceAge(),
				stu.getEntranceYear(),
				stu.getClazz(),
				stu.getSno(),
		});
	}

	public int updatePwd(String sno,String pwd) {
		String sql="update  student set password = ? where sno=?";

		return super.update(sql, new Object[] {pwd,sno});
	}

//	根据sno查找记录
	public List<Student> select(Student stu) {
		StringBuilder builder = new  StringBuilder();
		String sql="select * from student where  1=1";
		ArrayList<Object> list = new ArrayList<>();
		
		builder.append(sql);
		if (!stu.getSno().equals("".trim())){
			builder.append(" and sno LIKE ?");
			list.add('%' + stu.getSno() +  '%');
		}

		if (!stu.getSname().equals("".trim())){
			builder.append(" and sname LIKE ?");
			list.add('%' +stu.getSname()+  '%');
		}

		return super.selectAll(builder.toString(), list.toArray());
	}

	//	根据sno查找记录
	public String selectSql(Student stu) {
		StringBuilder builder = new  StringBuilder();
		String sql="select * from student where  1=1";


		builder.append(sql);
		if (!stu.getSno().equals("".trim())){
			builder.append(" and sno LIKE '%" +stu.getSno() + "%'");

		}

		if (!stu.getSname().equals("".trim())){
			builder.append(" and sname LIKE '%" +stu.getSname() + "%'");

		}

		return builder.toString();
	}

	
	//	根据sno修改数量
	public int del(String sno) {
		String sql="delete from student where sno=?";

		return super.update(sql, new Object[] {sno});
	}



	
	
	@Override
	public Student rowMapper(ResultSet rs) {
		// TODO Auto-generated method stub
		Student stu=new Student();

		try {
			stu.setSno(rs.getString("sno"));
			stu.setSname(rs.getString("sname"));
			stu.setSsex(rs.getString("ssex"));
			stu.setEntranceYear(rs.getInt("entrance_year"));
			stu.setEntranceAge(rs.getInt("entrance_age"));
			stu.setClazz(rs.getString("class"));
			stu.setPassword(rs.getString("password"));
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return stu;
	}
	
}
