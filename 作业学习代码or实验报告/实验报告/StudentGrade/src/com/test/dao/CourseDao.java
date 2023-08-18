package com.test.dao;




import com.test.pojo.Course;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;


public class CourseDao extends BaseDAO{

	public List<Course> selectAll(){
		//return new ArrayList<Course>();
		String sql="select * from v_course ";
		return super.selectAll(sql, new Object[] {});
	}

	public Course selectByCno(String cno){
		//return new ArrayList<Course>();
		String sql="select * from v_course where cno=?";
		return super.select(sql, new Object[] {cno});
	}
	
//	添加记录
	public int insertCourse(Course course) {
		String sql="insert into course  values(?,?,?,?)";
		return super.update(sql, new Object[] {
				course.getCno(),
				course.getCname(),
				course.getTno(),
				course.getCredit(),
				course.getFaceYear(),
				course.getCanceledYear()
		});
	}

	public int update(Course course) {
		String sql = "update course set cname=?,tno=?,credit=?,face_year=?,canceled_year=? where cno=?";
		return super.update(sql, new Object[]{

				course.getCname(),
				course.getTno(),
				course.getCredit(),
				course.getFaceYear(),
				course.getCanceledYear(),
				course.getCno(),
		});
	}

//	根据sno查找记录
	public List<Course> select(Course course) {
		StringBuilder builder = new  StringBuilder();
		String sql="select * from v_course where  1=1";
		ArrayList<Object> list = new ArrayList<>();
		
		builder.append(sql);
		if (!course.getCno().equals("".trim())){
			builder.append(" and cno LIKE ?");
			list.add('%' +course.getCno()+  '%');
		}
		if (!course.getCname().equals("".trim())){
			builder.append(" and cname LIKE ?");
			list.add('%' +course.getCname()+  '%');
		}
		if (!course.getTno().equals("".trim())){
			builder.append(" and tno LIKE ?");
			list.add('%' +course.getTno()+  '%');
		}


		return super.selectAll(builder.toString(), list.toArray());
	}

	//	根据sno查找记录
	public String selectSql(Course course) {
		StringBuilder builder = new  StringBuilder();
		String sql="select * from v_course where  1=1";

		builder.append(sql);
		if (!course.getCno().equals("".trim())){
			builder.append(" and cno LIKE '%" +course.getCno() + "%'");

		}
		if (!course.getCname().equals("".trim())){
			builder.append(" and cname LIKE '%" +course.getCname() + "%'");

		}
		if (!course.getTno().equals("".trim())){
			builder.append(" and tno LIKE ?");
		}

		return builder.toString();
	}

	
	//	根据sno修改数量
	public int del(String sno) {
		String sql="delete from course where cno=?";

		return super.update(sql, new Object[] {sno});
	}



	
	
	@Override
	public Course rowMapper(ResultSet rs) {
		// TODO Auto-generated method courseb
		Course course=new Course();
		try {
			course.setCno(rs.getString("cno"));
			course.setCname(rs.getString("cname"));
			course.setTno(rs.getString("tno"));
			course.setTname(rs.getString("tname"));
			course.setCredit(rs.getInt("credit"));
			course.setFaceYear(rs.getInt("face_year"));
			if (rs.getInt("canceled_year") == 0){
				course.setCanceledYear(null);
			}else {
				course.setCanceledYear(rs.getInt("canceled_year"));
			}

		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return course;
	}
	
}
