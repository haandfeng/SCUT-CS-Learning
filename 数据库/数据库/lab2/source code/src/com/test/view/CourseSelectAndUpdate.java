package  com.test.view;


import com.test.dao.CourseDao;
import com.test.pojo.Course;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.List;

public class CourseSelectAndUpdate extends JFrame  implements ActionListener {
	private static JPanel  panel,btnPanel, centerPanel,selectResultPane,coursePane,sqlPane;



	private JTextField txtcno,txtName, txtCcredit,txtTno,txtFaceYear,txtCanceledYear;

	private JLabel labCno,labName, labCcredit,labTno,labFaceYear,labCanceledYear;

	private JButton btnModify,btnDelete,btnAdd,btnSelect;

	private JTextArea sqlArea;

	private JTable table;

	private JScrollPane scrollPane;

	private CourseDao courseDao ;
	static String[] colName= {"CID","Course Name","Instructor ID","Instructor Name","Credit","Grade","Cancel year"};


	public CourseSelectAndUpdate(){
		setLayout(null);
		initService();
		setLocationRelativeTo(null);
		panel=new JPanel(new BorderLayout());
		setContentPane(panel);


		btnPanel=new JPanel();
		btnModify=new JButton("Update");
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

		Object[][] r1=getSelect(courseDao.selectAll());

		table=new JTable(r1,colName);
		scrollPane.setViewportView(table);
		scrollPane.setPreferredSize(new Dimension(660,200));
		selectResultPane.add(scrollPane);


		coursePane=new JPanel(new GridLayout(7,4));

		labCno=new JLabel("CID");
		labName=new JLabel("Course Name");
		labCcredit=new JLabel("Credit");
		labTno=new JLabel("Instructor ID");
		labFaceYear=new JLabel("Grade");
		labCanceledYear=new JLabel("Cancel year");

		txtcno=new JTextField(15);

		txtName=new JTextField(15);

		
		txtCcredit=new JTextField(15);

		txtTno=new JTextField(15);
		txtFaceYear=new JTextField(15);
		txtCanceledYear=new JTextField(15);


		coursePane.add(labCno);
		coursePane.add(txtcno);
		coursePane.add(labName);		
		coursePane.add(txtName);
		coursePane.add(labCcredit);		
		coursePane.add(txtCcredit);
		coursePane.add(labTno);
		coursePane.add(txtTno);
		coursePane.add(labFaceYear);
		coursePane.add(txtFaceYear);
		coursePane.add(labCanceledYear);
		coursePane.add(txtCanceledYear);

		sqlPane = new JPanel();
		sqlArea = new JTextArea(4,60);
		sqlArea.setEditable(false);

		sqlArea.setLineWrap(true);        //激活自动换行功能
		sqlArea.setWrapStyleWord(true);
//		JScrollPane scroll = new JScrollPane(sqlArea);
//		scroll.setSize (600,200) ;

		sqlPane.add(sqlArea);

		centerPanel.add(coursePane);
		centerPanel.add(selectResultPane);
		centerPanel.add(sqlPane);



		panel.add(centerPanel,BorderLayout.CENTER);




	}

	private void initService() {

		courseDao = new CourseDao();
	}

	public static Component getItemCom(){
		new CourseSelectAndUpdate();
		return panel;

	}


	
	public void actionPerformed(ActionEvent e){



		if(e.getSource()==btnDelete){
			String cno=txtcno.getText().trim();
			Course course = courseDao.selectByCno(cno);
			if (course == null){
				JOptionPane.showMessageDialog(null, "CID not exist","Information",JOptionPane.INFORMATION_MESSAGE);
				return;
			}
			
			int res = courseDao.del(cno);
			if (res > 0){


				JOptionPane.showMessageDialog(null, "Delete successfully");
				Object[][] r1=getSelect(courseDao.selectAll());

				table=new JTable(r1,colName);
				scrollPane.setViewportView(table);
			}

		}

		if(e.getSource()==btnModify){

			Course course = courseDao.selectByCno(txtcno.getText().trim());
			if (course == null){
				JOptionPane.showMessageDialog(null, "CID not exist","Information",JOptionPane.INFORMATION_MESSAGE);
				return;
			}

			course.setCname(txtName.getText().trim());
			
			course.setTno(txtTno.getText().trim());


			try{
				Integer credit = Integer.valueOf(txtCcredit.getText().trim());
				if (credit < 0){
					throw new Exception();
				}
				course.setCredit(credit);
				
			}catch (Exception ex){
				JOptionPane.showMessageDialog(null, "Fail,please enter correct credit","Information",JOptionPane.INFORMATION_MESSAGE);
				return;
			}

			if (course.getCname().equals("") || course.getTno().equals("") ){
				JOptionPane.showMessageDialog(null, "Fail, please enter all information again","Information",JOptionPane.INFORMATION_MESSAGE);
				return;
			}

			int i=courseDao.update(course);
			if(i>0){
				JOptionPane.showMessageDialog(null, "Modify successfully");
				Object[][] r1=getSelect(courseDao.selectAll());

				table=new JTable(r1,colName);
				scrollPane.setViewportView(table);
			}else {
				JOptionPane.showMessageDialog(null, "Operate fail");
			}


		}

		if(e.getSource()==btnAdd){
			String cno = txtcno.getText().trim();
			if (cno.length() != 7){
				JOptionPane.showMessageDialog(null, "Length of CID should be 7！","Information",JOptionPane.INFORMATION_MESSAGE);
				return;
			}
			Course course = courseDao.selectByCno(cno);
			if (course != null){
				JOptionPane.showMessageDialog(null, "CID has existed","Information",JOptionPane.INFORMATION_MESSAGE);
				return;
			}
			
			course=new Course();

			course.setCno(txtcno.getText().trim());

			course.setCname(txtName.getText().trim());

			course.setTno(txtTno.getText().trim());


			try{
				Integer credit = Integer.valueOf(txtCcredit.getText().trim());
				if (credit < 0){
					throw new Exception();
				}
				course.setCredit(credit);

			}catch (Exception ex){
				JOptionPane.showMessageDialog(null, "Insert fail，please enter correct credit","Information",JOptionPane.INFORMATION_MESSAGE);
				return;
			}
			if (course.getCname().equals("") || course.getTno().equals("") ){
				JOptionPane.showMessageDialog(null, "Insert fail，please enter all information again","Information",JOptionPane.INFORMATION_MESSAGE);
				return;
			}


			int i=courseDao.insertCourse(course);
			if(i>0){
				JOptionPane.showMessageDialog(null, "Insert successfully");
				Object[][] r1=getSelect(courseDao.selectAll());

				table=new JTable(r1,colName);
				scrollPane.setViewportView(table);
			}else {
				JOptionPane.showMessageDialog(null, "Operation fail");
			}


		}
		if(e.getSource()==btnSelect){

			Course course=new Course();
			course.setCno(txtcno.getText().trim());

			course.setCname(txtName.getText().trim());

			course.setTno(txtTno.getText().trim());




			List<Course> courses =  courseDao.select(course);
			
			Object[][] r1=getSelect(courses);

			table=new JTable(r1,colName);
			scrollPane.setViewportView(table);

			String sql = courseDao.selectSql(course);

			System.out.println(sql);
			sqlArea.setText(sql);
		}
	}

	Object[][] getSelect(List<Course> list){


		Object[][] results=new Object[list.size()][colName.length];

		for(int i=0;i<list.size();i++){
			Course course=list.get(i);
			results[i][0]=course.getCno();
			results[i][1]=course.getCname();
			results[i][2]=course.getTno();
			results[i][3]=course.getTname();
			results[i][4]=course.getCredit();
			results[i][5]=course.getFaceYear();
			if (course.getCanceledYear() != null){
				results[i][6]=course.getCanceledYear();
			}

		}

		return results;
	}


}
