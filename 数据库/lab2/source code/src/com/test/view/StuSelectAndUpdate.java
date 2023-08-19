package com.test.view;


import com.test.dao.*;
import com.test.pojo.Course;
import com.test.pojo.Student;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.util.List;

public class StuSelectAndUpdate extends JFrame  implements ActionListener {
	private static JPanel  panel,btnPanel, centerPanel,selectResultPane,stuPane,sqlPane;



	private JTextField txtsno,txtName, txtEntrancAge,txtEntrancYear,txtClazz;

	private JLabel labSno,labName,labSex, labEntrancAge,labEntrancYear,labClazz;

	private JButton btnModify,btnDelete,btnAdd,btnSelect;

	private JComboBox cmbSex;
	private JTextArea sqlArea;

	private JTable table;

	private JScrollPane scrollPane;

	private StudentDao stuDao ;
	static String[] colName= {"ID","Name","Sex","Age","Year","Grade"};



	public StuSelectAndUpdate(){
		setLayout(null);
		initService();
		setLocationRelativeTo(null);
		panel=new JPanel(new BorderLayout());
		setContentPane(panel);


		btnPanel=new JPanel();
		btnModify=new JButton("Modify");
		btnDelete=new JButton("Cancel");
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

		Object[][] r1=getSelect(stuDao.selectAll());

		table=new JTable(r1,colName);
		scrollPane.setViewportView(table);
		scrollPane.setPreferredSize(new Dimension(660,200));
		selectResultPane.add(scrollPane);


		stuPane=new JPanel(new GridLayout(6,4));

		labSno=new JLabel("ID");
		labName=new JLabel("Name");
		labSex=new JLabel("Sex");
		labEntrancAge=new JLabel("Age");
		labEntrancYear=new JLabel("Year");
		labClazz=new JLabel("Class");

		txtsno=new JTextField(15);

		txtName=new JTextField(15);

		cmbSex = new JComboBox();

		cmbSex.addItem("Unknown");
		cmbSex.addItem("男");
		cmbSex.addItem("女");
		txtEntrancAge=new JTextField(15);

		txtEntrancYear=new JTextField(15);
		txtClazz=new JTextField(15);


		stuPane.add(labSno);
		stuPane.add(txtsno);
		stuPane.add(labName);		
		stuPane.add(txtName);
		stuPane.add(labSex);
		stuPane.add(cmbSex);
		stuPane.add(labEntrancAge);		
		stuPane.add(txtEntrancAge);
		stuPane.add(labEntrancYear);
		stuPane.add(txtEntrancYear);
		stuPane.add(labClazz);
		stuPane.add(txtClazz);

		sqlPane = new JPanel();
		sqlArea = new JTextArea(4,60);
		sqlArea.setEditable(false);

		sqlArea.setLineWrap(true);        //激活自动换行功能
		sqlArea.setWrapStyleWord(true);
//		JScrollPane scroll = new JScrollPane(sqlArea);
//		scroll.setSize (600,200) ;

		sqlPane.add(sqlArea);

		centerPanel.add(stuPane);
		centerPanel.add(selectResultPane);
		centerPanel.add(sqlPane);



		panel.add(centerPanel,BorderLayout.CENTER);




	}

	private void initService() {

		stuDao = new StudentDao();
	}

	public static Component getItemCom(){
		new StuSelectAndUpdate();
		return panel;

	}


	
	public void actionPerformed(ActionEvent e){



		if(e.getSource()==btnDelete){
			String sno=txtsno.getText().trim();
			Student stu = stuDao.selectBySno(sno);
			if (stu == null){
				JOptionPane.showMessageDialog(null, "ID not exist","Information",JOptionPane.INFORMATION_MESSAGE);
				return;
			}


			int res = stuDao.del(sno);
			if (res > 0){


				JOptionPane.showMessageDialog(null, "Cancel successfully");
				Object[][] r1=getSelect(stuDao.selectAll());

				table=new JTable(r1,colName);
				scrollPane.setViewportView(table);
			}

		}

		if(e.getSource()==btnModify){
			String sno=txtsno.getText().trim();
			Student stu = stuDao.selectBySno(sno);
			if (stu == null){
				JOptionPane.showMessageDialog(null, "ID not exist","Information",JOptionPane.INFORMATION_MESSAGE);
				return;
			}

			String sex = cmbSex.getSelectedItem().toString();
			if (sex != "男" && sex != "女"){
				JOptionPane.showMessageDialog(null, "Failed to modify, please enter a valid gender","Information",JOptionPane.INFORMATION_MESSAGE);
				return;
			}
			stu.setSsex(sex);
			stu.setSname(txtName.getText().trim());
			stu.setClazz(txtClazz.getText().trim());




			try{
				Integer age = Integer.valueOf(txtEntrancAge.getText().trim());
				if (age < 10 || age > 50){
					throw new Exception();
				}
				Integer entranceYear = Integer.valueOf(txtEntrancYear.getText().trim());
				if (entranceYear < 0){
					throw new Exception();
				}
				stu.setEntranceAge(age);
				stu.setEntranceYear(entranceYear);

			}catch (Exception ex){
				JOptionPane.showMessageDialog(null, "Failed to modify, please enter a valid school age or school year","Information",JOptionPane.INFORMATION_MESSAGE);
				return;
			}

			if (stu.getSname().equals("") || stu.getClazz().equals("") ){
				JOptionPane.showMessageDialog(null, "Failed to modify, please enter a valid name","Information",JOptionPane.INFORMATION_MESSAGE);
				return;
			}
			int i=stuDao.update(stu);
			if(i>0){
				JOptionPane.showMessageDialog(null, "Modify successfully");
				Object[][] r1=getSelect(stuDao.selectAll());

				table=new JTable(r1,colName);
				scrollPane.setViewportView(table);
			}else {
				JOptionPane.showMessageDialog(null, "Operation fail");
			}


		}

		if(e.getSource()==btnAdd){
			String sno=txtsno.getText().trim();
			if (sno.length() != 10){
				JOptionPane.showMessageDialog(null, "ID length should be 10！","Information",JOptionPane.INFORMATION_MESSAGE);
				return;
			}
			Student stu = stuDao.selectBySno(sno);
			if (stu != null){
				JOptionPane.showMessageDialog(null, "ID has existed","Information",JOptionPane.INFORMATION_MESSAGE);
				return;
			}
			stu=new Student();
			stu.setSno(txtsno.getText().trim());

			String sex = cmbSex.getSelectedItem().toString();
			if (sex != "男" && sex != "女"){
				JOptionPane.showMessageDialog(null, "Insert fail, please enter a valid gender","Information",JOptionPane.INFORMATION_MESSAGE);
				return;
			}
			stu.setSsex(sex);
			stu.setSname(txtName.getText().trim());

			stu.setClazz(txtClazz.getText().trim());


			try{
				Integer age = Integer.valueOf(txtEntrancAge.getText().trim());
				if (age < 10 || age > 50){
					throw new Exception();
				}
				Integer entranceYear = Integer.valueOf(txtEntrancYear.getText().trim());
				if (entranceYear < 0){
					throw new Exception();
				}
				stu.setEntranceAge(age);
				stu.setEntranceYear(entranceYear);

			}catch (Exception ex){
				JOptionPane.showMessageDialog(null, "Insert to modify, please enter a valid school age or school year","Information",JOptionPane.INFORMATION_MESSAGE);
				return;
			}

			if (stu.getSname().equals("") || stu.getClazz().equals("") ){
				JOptionPane.showMessageDialog(null, "Insert fail, please enter all information","Information",JOptionPane.INFORMATION_MESSAGE);
				return;
			}

			int i=stuDao.insertStudent(stu);
			if(i>0){
				JOptionPane.showMessageDialog(null, "Insert successfully");
				Object[][] r1=getSelect(stuDao.selectAll());

				table=new JTable(r1,colName);
				scrollPane.setViewportView(table);
			}else {
				JOptionPane.showMessageDialog(null, "Operation fail");
			}


		}
		if(e.getSource()==btnSelect){

			Student stu=new Student();
			stu.setSno(txtsno.getText().trim());

			String sex = cmbSex.getSelectedItem().toString();
			if (sex == "Male" || sex == "Female"){
				stu.setSsex(sex);
			}

			stu.setSname(txtName.getText().trim());



			List<Student> stus =  stuDao.select(stu);
			
			Object[][] r1=getSelect(stus);

			table=new JTable(r1,colName);
			scrollPane.setViewportView(table);

			String sql = stuDao.selectSql(stu);

			System.out.println(sql);
			sqlArea.setText(sql);
		}
	}

	Object[][] getSelect(List<Student> list){


		Object[][] results=new Object[list.size()][colName.length];

		for(int i=0;i<list.size();i++){
			Student stu=list.get(i);
			results[i][0]=stu.getSno();
			results[i][1]=stu.getSname();
			results[i][2]=stu.getSsex();
			results[i][3]=stu.getEntranceAge();
			results[i][4]=stu.getEntranceYear();
			results[i][5]=stu.getClazz();
		}

		return results;
	}


}
