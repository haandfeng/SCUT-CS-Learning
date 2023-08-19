package com.test.dao;




import com.test.pojo.Sc;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;


public class ScDao extends BaseDAO{

	public List<Sc> selectAll(){
		//return new ArrayList<Sc>();
		String sql="select * from sc ";
		return super.selectAll(sql, new Object[] {});
	}

	public Sc selectSc(Sc sc){
		//return new ArrayList<Sc>();
		String sql="select * from sc where sno = ? and cno=? and tno = ? and chosen_year=?";
		return super.select(sql, new Object[] {
				sc.getSno(),
				sc.getCno(),
				sc.getTno(),
				sc.getYear()
		});
	}

	public Sc selectId(String id){
		//return new ArrayList<Sc>();
		String sql="select * from sc where id = ?";
		return super.select(sql, new Object[] {
				id
		});
	}
	
//	添加记录
	public int insertSc(Sc sc) {
		String sql="insert into sc (sno,cno,tno,chosen_year,score) values(?,?,?,?,?)";
		return super.update(sql, new Object[] {
				sc.getSno(),
				sc.getCno(),
				sc.getTno(),
				sc.getYear(),
				null
		});
	}

	public int update(Sc sc) {
		String sql = "update sc set sno=? , cno=?,tno=? , chosen_year=? WHERE id=?";
		return super.update(sql, new Object[]{

				sc.getSno(),
				sc.getCno(),
				sc.getTno(),
				sc.getYear(),
				sc.getId()
		});
	}
	public int updateScore(Sc sc) {
		String sql = "update sc set score=?  WHERE id=?";
		return super.update(sql, new Object[]{

				sc.getScore(),
				sc.getId()
		});
	}

//	根据sno查找记录
	public List<Sc> select(Sc sc) {
		StringBuilder builder = new  StringBuilder();
		String sql="select * from sc where  1=1";
		ArrayList<Object> list = new ArrayList<>();
		
		builder.append(sql);
		if (sc != null){
			if (sc.getId() != null){
				builder.append(" and id = ?");
				list.add(sc.getId());
			}
			if (sc.getSno() != null && !sc.getSno().equals("".trim())){
				builder.append(" and sno LIKE ?");
				list.add('%' +sc.getSno()+  '%');
			}
			if (sc.getCno() != null && !sc.getCno().equals("".trim())){
				builder.append(" and cno LIKE ?");
				list.add('%' +sc.getCno()+  '%');
			}
			if (sc.getTno() != null && !sc.getTno().equals("".trim())){
				builder.append(" and Tno LIKE ?");
				list.add('%' +sc.getTno()+  '%');
			}
		}



		return super.selectAll(builder.toString(), list.toArray());
	}

	//	根据sno查找记录
	public String selectSql(Sc sc) {
		StringBuilder builder = new  StringBuilder();
		String sql="select * from sc where  1=1";

		builder.append(sql);
		if (!sc.getSno().equals("".trim())){
			builder.append(" and sno LIKE '%" +sc.getSno() + "'%");
		}
		if (!sc.getCno().equals("".trim())){
			builder.append(" and cno LIKE '%" +sc.getCno() + "'%");
		}
		if (!sc.getTno().equals("".trim())){
			builder.append(" and Tno LIKE '%" +sc.getCno() + "'%");
		}
		return builder.toString();
	}

	
	//	根据sno修改数量
	public int del(String id) {
		String sql="delete from sc where id=? ";

		return super.update(sql, new Object[] {id});
	}



	
	
	@Override
	public Sc rowMapper(ResultSet rs) {
		// TODO Auto-generated method scb
		Sc sc=new Sc();
		try {
			sc.setId(rs.getInt("id"));
			sc.setSno(rs.getString("sno"));
			sc.setCno(rs.getString("cno"));
			sc.setTno(rs.getString("tno"));
			sc.setYear(rs.getInt("chosen_year"));
			if (rs.getObject("score") == null){
				sc.setScore(null);
			}else {
				sc.setScore(rs.getInt("score"));
			}

		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return sc;
	}
	
}
