import './style.css'

import * as echarts from 'echarts/core';
import { LineChart } from 'echarts/charts';
import { GridComponent, TooltipComponent, LegendComponent } from 'echarts/components';
import { CanvasRenderer } from 'echarts/renderers';

echarts.use([LineChart, GridComponent, TooltipComponent, CanvasRenderer, LegendComponent]);

const chartDom = document.getElementById('chart');
const myChart = echarts.init(chartDom);

async function update() {
    try {
        const dataResponse = await fetch('/api/data');

        if (!dataResponse.ok)
            throw new Error('HTTP ' + dataResponse.status);

        const data = await dataResponse.json();
        drawChart(data);
        document.getElementById('status').textContent = 'Online';
    }
    catch (error) {
        document.getElementById('status').textContent = 'Offline';
    }
}

function drawChart(data) {
  const series = [];
  if (data) {
    series[0] = {
      name: 'Sensor 1',
      type: 'line',
      showSymbol: false,
      data: data.map(el=>[el.timestamp, el.sensor_1]),
    }
    series[1] = {
      name: 'Sensor 2',
      type: 'line',
      showSymbol: false,
      data: data.map(el=>[el.timestamp, el.sensor_2]),
    }
  }
  const option = {
    tooltip: {
      trigger: 'axis',
      formatter: function (params) {
        let date = new Date(params[0].value[0]).toLocaleTimeString();
        let res = `<b>Time: ${date}</b><br/>`;
        params.forEach(item => {
          res += `${item.marker} ${item.seriesName}: ${item.value[1]} °C<br/>`;
        });
        return res;
      }
    },
    legend: {
      data: ['Sensor 1', 'Sensor 2'],
      top: '5%'
    },
    grid: {
      left: '10%',
      right: '10%',
      bottom: '15%'
    },
    xAxis: {
      type: 'time',
      splitLine: { show: false }
    },
    yAxis: {
      type: 'value',
      name: 'Value',
      splitLine: { show: true }
    },
    series
  };
  myChart.setOption(option);
}

update();
setInterval(update, 5000);