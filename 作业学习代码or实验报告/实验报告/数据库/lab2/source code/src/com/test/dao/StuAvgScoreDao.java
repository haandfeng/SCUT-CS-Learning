package com.test.dao;




import com.test.pojo.StuAvgScore;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.List;


public class StuAvgScoreDao extends BaseDAO{

	public StuAvgScore selectAvgScore(){

			String sql="select avg(score) as 'avgScore' from v_sc where score is not null " ;
		    return super.select(sql, new Object[] {});


	}

	@Override
	public StuAvgScore rowMapper(ResultSet rs) {
		// TODO Auto-generated method resb
		StuAvgScore res=new StuAvgScore();
		try {

			res.setAvgScore(rs.getDouble("avgScore"));

		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return res;
	}
	
}
