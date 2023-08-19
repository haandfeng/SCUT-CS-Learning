package com.test.view;


import com.test.dao.ClazzAvgScoreDao;
import com.test.pojo.ClazzAvgScore;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.List;

public class ClazzAvgScoreSelect extends JFrame  implements ActionListener {
	private static JPanel  panel,btnPanel, centerPanel,selectResultPane,selectPane;



	private JTextField txtClazz;

	private JLabel labClazz;

	private JButton btnSelect;



	private JTable table;

	private JScrollPane scrollPane;



	private ClazzAvgScoreDao clazzAvgScoreDao ;
	static String[] colSno= {"Class","AvgScore"};


	public ClazzAvgScoreSelect(){
		setLayout(null);
		initService();
		setLocationRelativeTo(null);
		panel=new JPanel(new BorderLayout());
		setContentPane(panel);


		btnPanel=new JPanel();
		btnSelect=new JButton("Search");

		btnSelect.addActionListener(this);


		btnPanel.add(btnSelect);
		panel.add(btnPanel,BorderLayout.NORTH);

		centerPanel=new JPanel();
		selectResultPane=new JPanel();


		table=new JTable();
		scrollPane=new JScrollPane(table);

		Object[][] r1=getSelect(clazzAvgScoreDao.selectClazzAvgScore(null));

		table=new JTable(r1,colSno);
		scrollPane.setViewportView(table);
		scrollPane.setPreferredSize(new Dimension(660,200));
		selectResultPane.add(scrollPane);


		selectPane=new JPanel(new GridLayout(1,2));



		labClazz=new JLabel("Class");

		txtClazz=new JTextField(15);



		selectPane.add(labClazz);
		selectPane.add(txtClazz);



		centerPanel.add(selectPane);
		centerPanel.add(selectResultPane);



		panel.add(centerPanel,BorderLayout.CENTER);




	}

	private void initService() {


		clazzAvgScoreDao = new ClazzAvgScoreDao();
	}

	public static Component getItemCom(){
		new ClazzAvgScoreSelect();
		return panel;

	}


	
	public void actionPerformed(ActionEvent e){



		if(e.getSource()==btnSelect){

			String sno=txtClazz.getText().trim();



			ClazzAvgScore sc = new ClazzAvgScore();
			sc.setClazz(sno);





			List<ClazzAvgScore> scList = clazzAvgScoreDao.selectClazzAvgScore(sc);
			
			Object[][] r1=getSelect(scList);

			table=new JTable(r1,colSno);
			scrollPane.setViewportView(table);


		}
	}

	Object[][] getSelect(List<ClazzAvgScore> list){


		Object[][] results=new Object[list.size()][colSno.length];

		for(int i=0;i<list.size();i++){
			ClazzAvgScore sc=list.get(i);
			results[i][0]=sc.getClazz();
			results[i][1]=sc.getAvgScore();


		}

		return results;
	}


}
