using UnityEngine;
using System.Net;
using System.Net.Sockets;
using System.Text;

public class MarkerController : MonoBehaviour
{
    public float markerX = 0;
    public float markerY = 0;

    private UdpClient udpClient;

    void Start()
    {
        udpClient = new UdpClient(5005);

        // Do not block Unity while waiting for UDP data
        

        Debug.Log("UDP started on port 5005");
    }
    void Update()
    {
        if (udpClient.Available > 0)
        {
            IPEndPoint remoteEndPoint =
                new IPEndPoint(IPAddress.Any, 0);

            byte[] data =
                udpClient.Receive(ref remoteEndPoint);

            string message =
                Encoding.UTF8.GetString(data);

            Debug.Log("UDP RECEIVED: " + message);

            string[] values = message.Split(',');

            if (values.Length == 2)
            {
                if (float.TryParse(values[0], out float x) &&
                    float.TryParse(values[1], out float y))
                {
                    markerX = x;
                    markerY = y;

                    float unityX =
                        Mathf.Lerp(-5f, 5f, markerX / 640f);

                    float unityY =
                        Mathf.Lerp(3f, -3f, markerY / 480f);

                    transform.position =
                        new Vector3(unityX, unityY, 0);
                }
            }
        }
    }

    void OnApplicationQuit()
    {
        udpClient?.Close();
    }
}