<template>
	<view class="content">
		<view class="text-area">
			Services
		</view>
		<view class="tab">
			<view class="tab_item">
				<image src="../../static/gd.png" mode=""></image>
				<view class="">Submit<br />homework</view>
			</view>
			<view @click="map()" class="tab_item">
				<image src="../../static/sd.png" mode=""></image>
				<view class="">Sign In</view>
			</view>
			<view class="tab_item">
				<image src="../../static/sj.png" mode=""></image>
				<view class="">Dedaline<br />List</view>
			</view>
			<view class="tab_item" >
				<image src="../../static/del.png" mode=""></image>
				<view class="">More</view>
			</view>
		</view>
		<view class="pjlist">
			<view class="">To Do List</view>
			<view style="font-size: 26rpx;">See More</view>
		</view>
		<view v-for="(item,index) in list" class="appraise">
			<view class="">
				<view class="">{{item.title}}</view>
				<view style="font-size: 24rpx; color: #c7c7c7;">28 Feb.20213 . 17:02</view>
			</view>
			<uni-rate readonly size="20" :touchable="false" :value="item.rate" @change="onChange" />
		</view>
		<view class="btn" @click="open">
			<view>Add</view>
		</view>
		<uni-popup ref="popup" type="center" :animation="true">
			<view class="popup">
				<view class="popup-content">
					Add
				</view>
				<uni-easyinput class="input" v-model="value" placeholder="Please enter a title"></uni-easyinput>
				<view  style="margin: 30rpx 0;">
						<uni-rate  :touchable="false" :value="1" @change="onChange" />
				</view>
			
				<view class="niu">
					<view class="" @click="close">close</view>
					<view class="" @click="add">confirm</view>
				</view>
			</view>
		</uni-popup>
	</view>
</template>

<script>
	export default {
		data() {
			return {
				list: [{
						title: 'General Physics hw',
						rate: 5,
						date: ''
					},
					{
						title: 'Data Structure work',
						rate: 3,
						date: ''
					},
				],
				value: '',
				rate: '',
			}
		},
		onLoad() {

		},
		methods: {
			open() {
				this.$refs.popup.open()
			},
			close() {
				this.$refs.popup.close()
			},
			add(){
				if(this.value!=''){
					this.list.push({title:this.value,rate:this.rate})
					this.$refs.popup.close()
					this.value=''
					this.rate=''
					uni.showToast({
						title: 'Add the successful',
						duration: 1000
					});
				}else{
					uni.showToast({
						title: 'Please enter a title',
						icon: 'none',
						duration: 2000
					});
				}
			
			},
			map() {
				uni.navigateTo({
					url: './map'
				})
			},
			onChange(e) {
				this.rate= e.value
				console.log(this.rate)
			}
		}
	}
</script>

<style lang="scss">
	.text-area {
		padding: 20rpx 55rpx;
	}

	.tab {
		width: 84%;
		display: flex;
		margin: 30rpx auto;
		justify-content: space-between;
		// align-items: center;
		font-size: 28rpx;
		line-height: 40rpx;
		text-align: center;
	}

	.tab_item {
		// width:22%;
		word-wrap: break-word;
		word-break: break-all;

		image {
			width: 100rpx;
			height: 100rpx;
		}
	}

	.pjlist {
		width: 84.5%;
		display: flex;
		align-items: center;
		margin: 70rpx auto 50rpx auto;
		justify-content: space-between;
	}

	.appraise {
		width: 75%;
		line-height: 52rpx;
		display: flex;
		margin-left: 20%;
		margin-bottom: 25rpx;
		justify-content: space-between;
		align-items: center;

		image {

			width: 210rpx;
			height: 90rpx;
		}
	}

	.btn {
		animation: pulse 2s linear infinite;
		position: fixed;
		bottom: 100rpx;
		left: 42.5%;
		border: 2rpx solid #0f60f7;
		width: 141rpx;
		height: 141rpx;
		border-radius: 50%;
		display: flex;
		align-items: center;
		view {
			margin: auto;
			text-align: center;
			background-color: #0f60f7;
			border-radius: 50%;
			width: 130rpx;
			height: 130rpx;
			line-height: 125rpx;
			color: #ebebeb;
		}
	}
	.popup {
		border-radius: 25rpx;
		background-color: #fff;
		padding: 20rpx 40rpx;
		.popup-content {
			font-size: 32rpx;
			color: #0f60f7;
			padding: 50rpx 250rpx;
		}

		.input {
			margin: auto;
			font-size: 28rpx;
		}
		.niu {
			justify-content: space-between;
			margin: auto;
			display: flex;
			padding: 30rpx 0 20rpx 0;

			view {
				background-color: #0f60f7;
				color: #f5f5f5;
				border-radius: 15rpx;
				padding: 5rpx 20rpx;
				font-size: 28rpx;
			}
		}
	}
@keyframes pulse  {
	
 0% {
        box-shadow: 0 0 0 0 #ffffff, 0 0 2px 3px #0f60f7, 0 0 1px 2px #00aaff, 0 0 2px 5px #0f60f7;
    }
    49.9% {
        box-shadow: 0 0 1px 30px #ffffff, 0 0 30px 25px #0f60f7, 0 0 1px 4px #ffffff, 0 0 6px 5px #0f60f7;
    }
    50% {
        box-shadow: 0 0 0 0 #ffffff, 0 0 2px 3px #0f60f7, 0 0 1px 10px #ffffff, 0 0 8px 5px #0f60f7;
    }
    100% {
        box-shadow: 0 0 0px 32px #ffffff, 0 0 32px 15px #0f60f7, 0 0 1px 15px #ffffff, 0 0 6px 21px #0f60f7;
    }
}
</style>
