package com.test.dao;




import com.test.pojo.CourseAvgScore;
import com.test.pojo.CourseAvgScore;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.List;


public class CourseAvgScoreDao extends BaseDAO{

	public List<CourseAvgScore> selectCourseAvgScore(CourseAvgScore sc){
		//return new ArrayList<CourseGrade>();
		StringBuilder builder = new  StringBuilder();
		String sql="select cno,cname,avg(score) as 'avgScore' from v_sc where score is not null ";


		builder.append(sql);
		if (sc != null){
			if (!sc.getCno().equals("".trim())){
				builder.append(" and cno LIKE '%" +sc.getCno() + "%'");

			}

			if (!sc.getCname().equals("".trim())){
				builder.append(" and cname LIKE '%" +sc.getCname() + "%'");
			}
		}

		builder.append(" group by cno");
		return super.selectAll(builder.toString(), new Object[] {});


	}


	
	@Override
	public CourseAvgScore rowMapper(ResultSet rs) {
		// TODO Auto-generated method resb
		CourseAvgScore res=new CourseAvgScore();
		try {
			res.setCno(rs.getString("cno"));
			res.setCname(rs.getString("cname"));

			res.setAvgScore(rs.getDouble("avgScore"));

		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return res;
	}
	
}
