package com.test.view;


import com.test.dao.CourseDao;
import com.test.dao.ScDao;
import com.test.dao.StudentDao;
import com.test.dao.TeacherDao;
import com.test.pojo.Course;
import com.test.pojo.Sc;
import com.test.pojo.Student;
import com.test.pojo.Teacher;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.List;

public class ScSelectAndUpdate extends JFrame  implements ActionListener {
	private static JPanel  panel,btnPanel, centerPanel,selectResultPane,scPane,sqlPane;



	private JTextField txtId,txtCno,txtSno, txtTno,txtYear;

	private JLabel labId,labCno,labSno,labTno, labYear;

	private JButton btnModify,btnDelete,btnAdd,btnSelect;

	private JTextArea sqlArea;

	private JTable table;

	private JScrollPane scrollPane;

	private CourseDao courseDao ;
	private StudentDao studentDao ;
	private TeacherDao teacherDao ;
	private ScDao scDao ;
	static String[] colSno= {"SCID","ID","CID","Instructor ID","Year","Score"};


	public ScSelectAndUpdate(){
		setLayout(null);
		initService();
		setLocationRelativeTo(null);
		panel=new JPanel(new BorderLayout());
		setContentPane(panel);


		btnPanel=new JPanel();
		btnModify=new JButton("Modify");
		btnDelete=new JButton("Delete");
		btnAdd=new JButton("Insert");
		btnSelect=new JButton("Search");

		btnSelect.addActionListener(this);
		btnModify.addActionListener(this);
		btnDelete.addActionListener(this);
		btnAdd.addActionListener(this);



		btnPanel.add(btnSelect);
		btnPanel.add(btnAdd);
		btnPanel.add(btnModify);
		btnPanel.add(btnDelete);
		panel.add(btnPanel,BorderLayout.NORTH);

		centerPanel=new JPanel();
		selectResultPane=new JPanel();


		table=new JTable();
		scrollPane=new JScrollPane(table);

		Object[][] r1=getSelect(scDao.selectAll());

		table=new JTable(r1,colSno);
		scrollPane.setViewportView(table);
		scrollPane.setPreferredSize(new Dimension(660,200));
		selectResultPane.add(scrollPane);


		scPane=new JPanel(new GridLayout(5,4));

		labId=new JLabel("SCID");
		labCno=new JLabel("CID");
		labSno=new JLabel("ID");
		labTno=new JLabel("Instructor ID");
		labYear=new JLabel("Year");

		txtId=new JTextField(15);
		txtCno=new JTextField(15);

		txtSno=new JTextField(15);
		txtTno=new JTextField(15);

		
		txtYear=new JTextField(15);

		scPane.add(labId);
		scPane.add(txtId);
		scPane.add(labSno);
		scPane.add(txtSno);
		scPane.add(labCno);
		scPane.add(txtCno);
		scPane.add(labTno);
		scPane.add(txtTno);
		scPane.add(labYear);		
		scPane.add(txtYear);


		sqlPane = new JPanel();
		sqlArea = new JTextArea(4,60);
		sqlArea.setEditable(false);

		sqlArea.setLineWrap(true);        //激活自动换行功能
		sqlArea.setWrapStyleWord(true);
//		JScrollPane scroll = new JScrollPane(sqlArea);
//		scroll.setSize (600,200) ;

		sqlPane.add(sqlArea);

		centerPanel.add(scPane);
		centerPanel.add(selectResultPane);
		centerPanel.add(sqlPane);



		panel.add(centerPanel,BorderLayout.CENTER);




	}

	private void initService() {

		courseDao = new CourseDao();
		studentDao = new StudentDao();
		teacherDao = new TeacherDao();
		scDao = new ScDao();
	}

	public static Component getItemCom(){
		new ScSelectAndUpdate();
		return panel;

	}


	
	public void actionPerformed(ActionEvent e){



		if(e.getSource()==btnDelete){
			String id=txtId.getText().trim();

			Sc sc = scDao.selectId(id);
			if (sc == null){
				JOptionPane.showMessageDialog(null, "Student selection information does not exist","Information",JOptionPane.INFORMATION_MESSAGE);
				return;
			}

			int res = scDao.del(id);
			if (res > 0){


				JOptionPane.showMessageDialog(null, "Delete success");
				Object[][] r1=getSelect(scDao.selectAll());

				table=new JTable(r1,colSno);
				scrollPane.setViewportView(table);
			}

		}

		if(e.getSource()==btnModify){
			String id=txtId.getText().trim();

			Sc sc = scDao.selectId(id);
			if (sc == null){
				JOptionPane.showMessageDialog(null, "Student selection information does not exist","Information",JOptionPane.INFORMATION_MESSAGE);
				return;
			}
			String sno=txtSno.getText().trim();
			Student stu = studentDao.selectBySno(sno);
			if (stu == null){
				JOptionPane.showMessageDialog(null, "ID not exist","Information",JOptionPane.INFORMATION_MESSAGE);
				return;
			}
			String cno=txtCno.getText().trim();
			Course course = courseDao.selectByCno(cno);
			if (course == null){
				JOptionPane.showMessageDialog(null, "CID not exist","Information",JOptionPane.INFORMATION_MESSAGE);
				return;
			}
			String tno=txtTno.getText().trim();
			Teacher teacher = teacherDao.selectByTno(tno);
			if (teacher == null){
				JOptionPane.showMessageDialog(null, "Instructor information not exist","Information",JOptionPane.INFORMATION_MESSAGE);
				return;
			}
			if (stu.getEntranceYear() > course.getFaceYear()){
				//学生年级应该高于等于课程年级
				System.out.println(stu.getEntranceYear());
				System.out.println(course.getFaceYear());
				JOptionPane.showMessageDialog(null, "The student grade should be higher than the course grade","Information",JOptionPane.INFORMATION_MESSAGE);
				return;
			}

			sc.setSno(sno);
			sc.setCno(cno);
			sc.setTno(tno);


			try{
				Integer year = Integer.valueOf(txtYear.getText().trim());
				if (year < 0){
					throw new Exception();
				}
				sc.setYear(year);
				
			}catch (Exception ex){
				JOptionPane.showMessageDialog(null, "Failed to modify. Please enter a valid year","Information",JOptionPane.INFORMATION_MESSAGE);
				return;
			}
			Sc sc1 = scDao.selectSc(sc);
			if (sc1 != null && !sc.getId().equals(id)){
				JOptionPane.showMessageDialog(null, "Modification failed, the course selection information already exists","Information",JOptionPane.INFORMATION_MESSAGE);
				return;
			}

			if (course.getCanceledYear() != null){
				if (sc.getYear() >= course.getCanceledYear()){
					JOptionPane.showMessageDialog(null, "The course has been cancelled for that year","Information",JOptionPane.INFORMATION_MESSAGE);
					return;
				}
			}


			int i=scDao.update(sc);
			if(i>0){
				JOptionPane.showMessageDialog(null, "Modify successfully");
				Object[][] r1=getSelect(scDao.selectAll());

				table=new JTable(r1,colSno);
				scrollPane.setViewportView(table);
			}else {
				JOptionPane.showMessageDialog(null, "Operation fail");
			}


		}

		if(e.getSource()==btnAdd){
			String sno=txtSno.getText().trim();
			Student stu = studentDao.selectBySno(sno);
			if (stu == null){
				JOptionPane.showMessageDialog(null, "ID not exist","Information",JOptionPane.INFORMATION_MESSAGE);
				return;
			}
			String cno=txtCno.getText().trim();
			Course course = courseDao.selectByCno(cno);
			if (course == null){
				JOptionPane.showMessageDialog(null, "CID not exist","Information",JOptionPane.INFORMATION_MESSAGE);
				return;
			}
			String tno=txtTno.getText().trim();
			Teacher teacher = teacherDao.selectByTno(tno);
			if (teacher == null){
				JOptionPane.showMessageDialog(null, "Instructor information not exist","Information",JOptionPane.INFORMATION_MESSAGE);
				return;
			}

			if (stu.getEntranceYear() > course.getFaceYear()){
				//学生年级应该高于等于课程年级
				System.out.println(stu.getEntranceYear());
				System.out.println(course.getFaceYear());
				JOptionPane.showMessageDialog(null, "The student grade should be higher than the course grade","Information",JOptionPane.INFORMATION_MESSAGE);
				return;
			}



			Sc sc = new Sc();
			sc.setSno(sno);
			sc.setCno(cno);
			sc.setTno(tno);
			try{
				Integer year = Integer.valueOf(txtYear.getText().trim());
				if (year < 0){
					throw new Exception();
				}
				sc.setYear(year);

			}catch (Exception ex){
				JOptionPane.showMessageDialog(null, "Failed to modify. Please enter a valid yea","Information",JOptionPane.INFORMATION_MESSAGE);
				return;
			}

			Sc sc1 = scDao.selectSc(sc);
			if (sc1 != null){
				JOptionPane.showMessageDialog(null, "Student course selection information already exists","Information",JOptionPane.INFORMATION_MESSAGE);
				return;
			}

			if (course.getCanceledYear() != null){
				if (sc.getYear() >= course.getCanceledYear()){
					JOptionPane.showMessageDialog(null, "The course has been cancelled for that year","Information",JOptionPane.INFORMATION_MESSAGE);
					return;
				}
			}


			int i=scDao.insertSc(sc);
			if(i>0){
				JOptionPane.showMessageDialog(null, "Insert successfully");
				Object[][] r1=getSelect(scDao.selectAll());

				table=new JTable(r1,colSno);
				scrollPane.setViewportView(table);
			}else {
				JOptionPane.showMessageDialog(null, "Operation fail");
			}


		}
		if(e.getSource()==btnSelect){

			String sno=txtSno.getText().trim();
		
			String cno=txtCno.getText().trim();

			String tno=txtTno.getText().trim();




			Sc sc = new Sc();
			sc.setSno(sno);
			sc.setCno(cno);
			sc.setTno(tno);




			List<Sc> scList =  scDao.select(sc);
			
			Object[][] r1=getSelect(scList);

			table=new JTable(r1,colSno);
			scrollPane.setViewportView(table);

			String sql = scDao.selectSql(sc);

			System.out.println(sql);
			sqlArea.setText(sql);
		}
	}

	Object[][] getSelect(List<Sc> list){


		Object[][] results=new Object[list.size()][colSno.length];

		for(int i=0;i<list.size();i++){
			Sc sc=list.get(i);
			results[i][0]=sc.getId();
			results[i][1]=sc.getSno();
			results[i][2]=sc.getCno();
			results[i][3]=sc.getTno();
			results[i][4]=sc.getYear();
			if (sc.getScore() != null){
				results[i][5]=sc.getScore();
			}

		}

		return results;
	}


}
