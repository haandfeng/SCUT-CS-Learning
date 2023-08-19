package com.test.pojo;

public class Student {
	private String sno;
	private String sname;
	private String ssex;
	private Integer entranceAge;
	private Integer entranceYear;
	private String clazz;

	private String password;

	public Student() {
		
	}

	public String getSno() {
		return sno;
	}

	public void setSno(String sno) {
		this.sno = sno;
	}

	public String getSname() {
		return sname;
	}

	public void setSname(String sname) {
		this.sname = sname;
	}

	public String getSsex() {
		return ssex;
	}

	public void setSsex(String ssex) {
		this.ssex = ssex;
	}

	public Integer getEntranceAge() {
		return entranceAge;
	}

	public void setEntranceAge(Integer entranceAge) {
		this.entranceAge = entranceAge;
	}

	public Integer getEntranceYear() {
		return entranceYear;
	}

	public void setEntranceYear(Integer entranceYear) {
		this.entranceYear = entranceYear;
	}

	public String getClazz() {
		return clazz;
	}

	public void setClazz(String clazz) {
		this.clazz = clazz;
	}

	public String getPassword() {
		return password;
	}

	public void setPassword(String password) {
		this.password = password;
	}
}
