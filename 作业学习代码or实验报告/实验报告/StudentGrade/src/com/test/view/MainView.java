package com.test.view;

import com.test.pojo.StuAvgScore;
import com.test.pojo.User;

import java.awt.*;

import javax.swing.*;
import javax.swing.border.EmptyBorder;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import javax.swing.border.TitledBorder;
import javax.swing.border.LineBorder;
import javax.swing.border.EtchedBorder;

public class MainView extends JFrame {

	private JPanel contentPane;
	CardLayout cardLayout=new CardLayout();

	static Dimension frameSize = new Dimension(900, 600);
	ImageIcon imageIcon = new ImageIcon(this.getClass().getResource(
			"/1.png"));

	/**
	 * Launch the application.
	 */
	/**
	 * Create the frame.
	 */
	public MainView(User user) {
		setTitle("学生选课系统(管理员)");
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		//setBounds(100, 100, 900, 600);
		setSize(frameSize);
		setLocationRelativeTo(null);

		contentPane = new JPanel();
		contentPane.setBorder(new TitledBorder(null, "主界面", TitledBorder.LEADING, TitledBorder.TOP, null, null));
		setContentPane(contentPane);
		contentPane.setLayout(null);



		JPanel panel = new JPanel();
		panel.setBorder(new TitledBorder(new EtchedBorder(EtchedBorder.LOWERED, new Color(255, 255, 255), new Color(160, 160, 160)), "学生选课系统", TitledBorder.LEADING, TitledBorder.TOP, null, new Color(0, 0, 0)));
		panel.setBounds(117, 10, 750, 500);
		contentPane.add(panel);
		panel.setLayout(cardLayout);


//		添加面板



		panel.add(StuSelectAndUpdate.getItemCom(),"stuView");
		panel.add(TeaSelectAndUpdate.getItemCom(),"teaView");
		panel.add(CourseSelectAndUpdate.getItemCom(),"courseView");
		panel.add(ScSelectAndUpdate.getItemCom(),"scView");
		panel.add(StuGradeSelect.getItemCom(),"stuGradeView");
		panel.add(StuAvgScoreSelect.getItemCom(),"stuAvgScoreView");
		panel.add(CourseAvgScoreSelect.getItemCom(),"couAvgScoreView");
		panel.add(ClazzAvgScoreSelect.getItemCom(),"clazzAvgScoreView");
		panel.add(UserUpdatePwd.getItemCom(user),"pwdView");


		

		
		JPanel panel_1 = new JPanel();
		panel_1.setBorder(new TitledBorder(null, "菜单", TitledBorder.LEADING, TitledBorder.TOP, null, null));
		panel_1.setBounds(10, 34, 120, 400);
		contentPane.add(panel_1);
		panel_1.setLayout(null);
		
		JButton btnNewButton = new JButton("学生管理");
		btnNewButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				cardLayout.show(panel, "stuView");
			}
		});
		btnNewButton.setBounds(0, 26, 97, 23);
		panel_1.add(btnNewButton);
		
		JButton btnNewButton_1 = new JButton("教师管理");
		btnNewButton_1.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				cardLayout.show(panel, "teaView");
			}
		});
		btnNewButton_1.setBounds(0, 59, 97, 23);
		panel_1.add(btnNewButton_1);
		
		JButton btnNewButton_2 = new JButton("课程管理");
		btnNewButton_2.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				cardLayout.show(panel, "courseView");
			}
		});
		btnNewButton_2.setBounds(0, 92, 97, 23);
		panel_1.add(btnNewButton_2);
		
		JButton btnNewButton_2_1 = new JButton("学生选课");
		btnNewButton_2_1.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				cardLayout.show(panel, "scView");
			}
		});
		btnNewButton_2_1.setBounds(0, 127, 97, 23);
		panel_1.add(btnNewButton_2_1);

		JButton btnNewButton_2_2 = new JButton("多表查询");
		btnNewButton_2_2.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				cardLayout.show(panel, "stuGradeView");
			}
		});
		btnNewButton_2_2.setBounds(0, 161, 97, 23);
		panel_1.add(btnNewButton_2_2);

		JButton btnNewButton_2_3 = new JButton("学生成绩");
		btnNewButton_2_3.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				cardLayout.show(panel, "stuAvgScoreView");
			}
		});
		btnNewButton_2_3.setBounds(0, 195, 97, 23);
		panel_1.add(btnNewButton_2_3);

		JButton btnNewButton_2_4 = new JButton("班级成绩");
		btnNewButton_2_4.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				cardLayout.show(panel, "clazzAvgScoreView");
			}
		});
		btnNewButton_2_4.setBounds(0, 230, 97, 23);
		panel_1.add(btnNewButton_2_4);

		JButton btnNewButton_2_5 = new JButton("课程成绩");
		btnNewButton_2_5.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				cardLayout.show(panel, "couAvgScoreView");
			}
		});
		btnNewButton_2_5.setBounds(0, 265, 97, 23);
		panel_1.add(btnNewButton_2_5);

		JButton btnNewButton_3 = new JButton("修改密码");
		btnNewButton_3.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				cardLayout.show(panel, "pwdView");
			}
		});
		btnNewButton_3.setBounds(0, 300, 97, 23);
		panel_1.add(btnNewButton_3);

		
		JButton btnNewButton_2_1_1 = new JButton("退出");
		btnNewButton_2_1_1.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				Login login=new Login();
				login.setVisible(true);
				dispose();
			}
		});
		btnNewButton_2_1_1.setBounds(0, 335, 97, 23);
		panel_1.add(btnNewButton_2_1_1);

		addImageByJLable();

	}
	public void addImageByJLable() {
		setLayout(null);
		// 设置背景
		JLabel lbBg = new JLabel(imageIcon);
		lbBg.setBounds(0, 0, this.getWidth(), this.getHeight());
		this.getContentPane().add(lbBg);
		setVisible(true);
	}

	public static void main(String[] args) {
		MainView main=new MainView(new User());
		main.setVisible(true);
	}
}
