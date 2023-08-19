package com.test.pojo;

public class Course {
	private String cno;
	private String cname;
	private String tno;
	private String tname;
	private Integer credit;
	private Integer faceYear;
	private Integer canceledYear;


	public Course() {

	}

	public String getCno() {
		return cno;
	}

	public void setCno(String cno) {
		this.cno = cno;
	}

	public String getCname() {
		return cname;
	}

	public void setCname(String cname) {
		this.cname = cname;
	}

	public String getTno() {
		return tno;
	}

	public void setTno(String tno) {
		this.tno = tno;
	}

	public String getTname() {
		return tname;
	}

	public void setTname(String tname) {
		this.tname = tname;
	}

	public Integer getCredit() {
		return credit;
	}

	public void setCredit(Integer credit) {
		this.credit = credit;
	}

	public Integer getCanceledYear() {
		return canceledYear;
	}

	public void setCanceledYear(Integer canceledYear) {
		this.canceledYear = canceledYear;
	}

	public Integer getFaceYear() {
		return faceYear;
	}

	public void setFaceYear(Integer faceYear) {
		this.faceYear = faceYear;
	}
}
