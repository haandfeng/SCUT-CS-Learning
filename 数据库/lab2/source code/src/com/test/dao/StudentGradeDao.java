package com.test.dao;




import com.test.pojo.StudentGrade;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;


public class StudentGradeDao extends BaseDAO{

	public List<StudentGrade> selectAll(){
		//return new ArrayList<StudentGrade>();
		String sql="select * from v_sc " ;
		return super.selectAll(sql, new Object[] {});
	}





//	根据sno查找记录
	public List<StudentGrade> select(StudentGrade res) {
		StringBuilder builder = new  StringBuilder();
		String sql="select * from v_sc where  1=1 ";

		ArrayList<Object> list = new ArrayList<>();
		
		builder.append(sql);

		if (!res.getSno().equals("".trim())){
			builder.append(" and sno LIKE ?");
			list.add('%' + res.getSno() +  '%');
		}

		if (!res.getSname().equals("".trim())){
			builder.append(" and sname LIKE ?");
			list.add('%' +res.getSname()+  '%');
		}

		if (!res.getCno().equals("".trim())){
			builder.append(" and cno LIKE ?");
			list.add('%' +res.getCno()+  '%');
		}
		if (!res.getCname().equals("".trim())){
			builder.append(" and cname LIKE ?");
			list.add('%' +res.getCname()+  '%');
		}
		if (!res.getTno().equals("".trim())){
			builder.append(" and tno LIKE ?");
			list.add('%' +res.getTno()+  '%');
		}
		if (res.getTname() != null){
			builder.append(" and tname LIKE ?");
			list.add('%' +res.getTname()+  '%');
		}


		return super.selectAll(builder.toString(), list.toArray());
	}

	//	根据sno查找记录
	public String selectSql(StudentGrade res) {
		StringBuilder builder = new  StringBuilder();
		String sql="select * from res where  1=1";

		builder.append(sql);

		if (!res.getSno().equals("".trim())){
			builder.append(" and sno LIKE '%" +res.getSno() + "%'");

		}

		if (!res.getSname().equals("".trim())){
			builder.append(" and sname LIKE '%" +res.getSname() + "%'");

		}

		if (!res.getCno().equals("".trim())){
			builder.append(" and cno LIKE '%" +res.getCno() + "%'");

		}
		if (!res.getCname().equals("".trim())){
			builder.append(" and cname LIKE '%" +res.getCname() + "%'");

		}
		if (!res.getTno().equals("".trim())){
			builder.append(" and tno LIKE '%" +res.getTno() + "%'");

		}
		if (!res.getTname().equals("".trim())){
			builder.append(" and tname LIKE '%" +res.getTname() + "%'");

		}
		return builder.toString();
	}
	
	
	@Override
	public StudentGrade rowMapper(ResultSet rs) {
		// TODO Auto-generated method resb
		StudentGrade res=new StudentGrade();
		try {
			res.setSno(rs.getString("sno"));
			res.setSname(rs.getString("sname"));
			res.setSsex(rs.getString("ssex"));
			res.setEntranceYear(rs.getInt("entrance_year"));
			res.setEntranceAge(rs.getInt("entrance_age"));
			res.setClazz(rs.getString("class"));

			res.setCno(rs.getString("cno"));
			res.setCname(rs.getString("cname"));
			res.setTno(rs.getString("tno"));
			res.setTname(rs.getString("tname"));
			res.setCredit(rs.getInt("credit"));

			res.setYear(rs.getInt("chosen_year"));
			if (rs.getObject("score") == null){
				res.setScore(null);
			}else {
				res.setScore(rs.getInt("score"));
			}
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return res;
	}
	
}
