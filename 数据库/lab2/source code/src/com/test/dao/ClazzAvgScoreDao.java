package com.test.dao;




import com.test.pojo.ClazzAvgScore;
import com.test.pojo.StuAvgScore;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.List;


public class ClazzAvgScoreDao extends BaseDAO{



	public List<ClazzAvgScore> selectClazzAvgScore(ClazzAvgScore sc){
		//return new ArrayList<StudentGrade>();
		StringBuilder builder = new  StringBuilder();
		String sql="select class,avg(score) as 'avgScore' from v_sc where score is not null ";


		builder.append(sql);
		if (sc != null){
			if (!sc.getClazz().equals("".trim())){
				builder.append(" and class LIKE '%" +sc.getClazz() + "%'");

			}
		}


		builder.append(" group by class");
		return super.selectAll(builder.toString(), new Object[] {});


	}


	
	@Override
	public ClazzAvgScore rowMapper(ResultSet rs) {
		// TODO Auto-generated method resb
		ClazzAvgScore res=new ClazzAvgScore();
		try {
			res.setClazz(rs.getString("class"));

			res.setAvgScore(rs.getDouble("avgScore"));

		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return res;
	}
	
}
