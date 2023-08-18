package com.test.dao;




import com.test.pojo.StuAvgScore;
import com.test.pojo.StudentGrade;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;


public class StudentAvgScoreDao extends BaseDAO{


	public List<StuAvgScore> selectStudentAvgScore(StuAvgScore sc){
		//return new ArrayList<StudentGrade>();
		StringBuilder builder = new  StringBuilder();
		String sql="select sno,sname,avg(score) as 'avgScore' from v_sc where score is not null ";


		builder.append(sql);
		if (sc != null){
			if (!"".trim().equals(sc.getSno())){
				builder.append(" and sno LIKE '%" +sc.getSno() + "%'");

			}

			if (!"".trim().equals(sc.getSname())){
				builder.append(" and sname LIKE '%" +sc.getSname() + "%'");

			}
		}

		builder.append(" group by sno");
		return super.selectAll(builder.toString(), new Object[] {});


	}


	
	@Override
	public StuAvgScore rowMapper(ResultSet rs) {
		// TODO Auto-generated method resb
		StuAvgScore res=new StuAvgScore();
		try {
			res.setSno(rs.getString("sno"));
			res.setSname(rs.getString("sname"));

			res.setAvgScore(rs.getDouble("avgScore"));

		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return res;
	}
	
}
