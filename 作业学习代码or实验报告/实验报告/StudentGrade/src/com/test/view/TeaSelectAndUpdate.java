package com.test.view;


import com.test.dao.TeacherDao;
import com.test.pojo.Teacher;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.List;

public class TeaSelectAndUpdate extends JFrame  implements ActionListener {
	private static JPanel  panel,btnPanel, centerPanel,selectResultPane,teaPane,sqlPane;



	private JTextField txttno,txtName;

	private JLabel labTno,labName;

	private JButton btnModify,btnDelete,btnAdd,btnSelect;


	private JTextArea sqlArea;

	private JTable table;

	private JScrollPane scrollPane;

	private TeacherDao teaDao ;
	static String[] colName= {"教师编号","姓名","所授课程列表"};


	public TeaSelectAndUpdate(){
		setLayout(null);
		initService();
		setLocationRelativeTo(null);
		panel=new JPanel(new BorderLayout());
		setContentPane(panel);


		btnPanel=new JPanel();
		btnModify=new JButton("修改");
		btnDelete=new JButton("删除");
		btnAdd=new JButton("新增");
		btnSelect=new JButton("查询");

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

		Object[][] r1=getSelect(teaDao.selectAll());

		table=new JTable(r1,colName);
		scrollPane.setViewportView(table);
		scrollPane.setPreferredSize(new Dimension(660,200));
		selectResultPane.add(scrollPane);


		teaPane=new JPanel(new GridLayout(5,4));

		labTno=new JLabel("教师编号");
		labName=new JLabel("姓名");


		txttno=new JTextField(15);

		txtName=new JTextField(15);




		teaPane.add(labTno);
		teaPane.add(txttno);
		teaPane.add(labName);		
		teaPane.add(txtName);

		sqlPane = new JPanel();
		sqlArea = new JTextArea(4,60);
		sqlArea.setEditable(false);

		sqlArea.setLineWrap(true);        //激活自动换行功能
		sqlArea.setWrapStyleWord(true);
//		JScrollPane scroll = new JScrollPane(sqlArea);
//		scroll.setSize (600,200) ;

		sqlPane.add(sqlArea);

		centerPanel.add(teaPane);
		centerPanel.add(selectResultPane);
		centerPanel.add(sqlPane);



		panel.add(centerPanel,BorderLayout.CENTER);




	}

	private void initService() {

		teaDao = new TeacherDao();
	}

	public static Component getItemCom(){
		new TeaSelectAndUpdate();
		return panel;

	}


	
	public void actionPerformed(ActionEvent e){



		if(e.getSource()==btnDelete){
			String tno=txttno.getText().trim();
			Teacher tea = teaDao.selectByTno(tno);
			if (tea == null){
				JOptionPane.showMessageDialog(null, "教师编号不存在","提示",JOptionPane.INFORMATION_MESSAGE);
				return;
			}
			
			int res = teaDao.del(tno);
			if (res > 0){


				JOptionPane.showMessageDialog(null, "删除成功");
				Object[][] r1=getSelect(teaDao.selectAll());

				table=new JTable(r1,colName);
				scrollPane.setViewportView(table);
			}

		}

		if(e.getSource()==btnModify){
			String tno=txttno.getText().trim();
			Teacher tea = teaDao.selectByTno(tno);
			if (tea == null){
				JOptionPane.showMessageDialog(null, "教师编号不存在","提示",JOptionPane.INFORMATION_MESSAGE);
				return;
			}


			tea.setTname(txtName.getText().trim());


			if (tea.getTname().equals("")  ){
				JOptionPane.showMessageDialog(null, "修改失败，请输入所有信息","提示",JOptionPane.INFORMATION_MESSAGE);
				return;
			}
			int i=teaDao.update(tea);
			if(i>0){
				JOptionPane.showMessageDialog(null, "修改成功");
				Object[][] r1=getSelect(teaDao.selectAll());

				table=new JTable(r1,colName);
				scrollPane.setViewportView(table);
			}else {
				JOptionPane.showMessageDialog(null, "操作失败");
			}


		}

		if(e.getSource()==btnAdd){
			String tno=txttno.getText().trim();
			if (tno.length() != 5){
				JOptionPane.showMessageDialog(null, "教师编号长度为5！","提示",JOptionPane.INFORMATION_MESSAGE);
				return;
			}
			Teacher tea = teaDao.selectByTno(tno);
			if (tea != null){
				JOptionPane.showMessageDialog(null, "教师编号已存在","提示",JOptionPane.INFORMATION_MESSAGE);
				return;
			}
			tea=new Teacher();
			tea.setTno(txttno.getText().trim());


			tea.setTname(txtName.getText().trim());




			if (tea.getTname().equals("")  ){
				JOptionPane.showMessageDialog(null, "新增失败，请输入所有信息","提示",JOptionPane.INFORMATION_MESSAGE);
				return;
			}

			int i=teaDao.insertTeacher(tea);
			if(i>0){
				JOptionPane.showMessageDialog(null, "新增成功");
				Object[][] r1=getSelect(teaDao.selectAll());

				table=new JTable(r1,colName);
				scrollPane.setViewportView(table);
			}else {
				JOptionPane.showMessageDialog(null, "操作失败");
			}


		}
		if(e.getSource()==btnSelect){

			Teacher tea=new Teacher();
			tea.setTno(txttno.getText().trim());



			tea.setTname(txtName.getText().trim());



			List<Teacher> teas =  teaDao.select(tea);
			
			Object[][] r1=getSelect(teas);

			table=new JTable(r1,colName);
			scrollPane.setViewportView(table);

			String sql = teaDao.selectSql(tea);

			System.out.println(sql);
			sqlArea.setText(sql);
		}
	}

	Object[][] getSelect(List<Teacher> list){


		Object[][] results=new Object[list.size()][colName.length];

		for(int i=0;i<list.size();i++){
			Teacher tea=list.get(i);
			results[i][0]=tea.getTno();
			results[i][1]=tea.getTname();
			results[i][2]=tea.getCourses();
		}

		return results;
	}


}
